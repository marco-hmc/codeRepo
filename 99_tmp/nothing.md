VsString定义
```c++
typedef struct VsString
 {
    unsigned short none; /* This VsString is a normal OmName if none is not 0. */
    unsigned short type; /* If none is 0, VsString is dynamic allocation if type is 1,
                            ** and VsString has fixed length if type is 2,
                            ** and VsString should be stored into database if type is 3. */
    unsigned int size;   /* VsString string length */
    unsigned int ptr[2]; /* string pointer */
    unsigned int idx;    /* database index if type is 3  */
    unsigned int cap;    /* VsString allocation size */
    unsigned int pad1;   /* spare */
    unsigned int pad2;   /* spare */
 } VsString;
```
VsString有四种形式（用法）

定义并初始化一个VsString对象：VsString bin_name = { 0x0000, 0x0000 }，暂不把它归类为一种形式，因为我们在使用其前要使用一些接口再次“赋值初始化”，就以赋值初始化后的形式归类。
形式	解释
* 形式1：none不为0x0000，保存长度小于32位的字符	用自身空间来保存长度小于32位的字符，因此其他成员毫无意义，就像一个32位的char型数组，与平台OmName相似，保存小于32位字符时，OmNameNew和OmNameCreate”创建“的字符串为这种形式。
* 形式2：none 为0x0000，type ==0x0001	动态分配空间保存长度大于32位的字符，自身拥有这份内存，因此需要负责内存回收。初始创建时（OmNameNew）动态分配一块恰好容纳初始字符串的空间，成员ptr指向这块空间。size为字符串长度，cap为空间大小，可以使用OmNameSet/OmNameCpy更改存储字符串值（可能会扩大内存空间大小，但不会减少空间，也不会转换为形式1）。
* 形式3：none 为0x0000，type ==0x0002	代理一块变量的内存（OmNameProxy），这块内存的空间必须大于32字节，自身不负责内存的管理，一旦确定“代理关系”，这块内存大小就固定了，因此被代理的变量生命周期一定要比VsString生命周期长。初始size为0，cap为代理内存空间大小，意味着它只使用被代理字符串的空间，不负责原始内容。可以使用OmNameSet更改存储字符串值（内存空间大小不变），OmNameDel不会清除这段不属于自己的内存。
* 形式4：none 为0x0000，type ==0x0003	指向一块数据库VSTRING对象的内存来保存超过32位的字符（OmNameCreate），idx为该数据库对象的id，相当于用VsString对象管理一个数据库对象，需要负责管理数据库对象的生命周期。size为字符串长度，cap为空间大小。使用OmNameModify来修改字符串的值，OmNameDelete删除对象。


看完上表的介绍，我们对VsString有了初步了解，我们发现对于上面四种形式，他们存在着一定的关系，即形式1作为基础，可以转变为形式2和形式4；形式4可以“退化“为形式1
决定他们性质的是一堆”初始化赋值“ 函数和更改函数，这些函数接口决定了他们向何种方向转换。
形式4作为数据库对象使用，是要被理解的，使用一个定长数据结构保存另一个数据库成员索引。而形式2涉及到动态内存管理，要在命令过程中使用。
对于如何使用这个对象和函数，对于不经常接触的人来说，现在可能依旧一脸茫然，请基于上面认知，结合下列陷阱，来正确认识VsString使用的接口。
VsString使用陷阱与缺陷
VsString陷阱
* 陷阱1：在命令中使用OmNameNew创建一个对象，用作参数或者其他用途，最后没有调用OmNameDel释放内存，造成内存泄露。
* 陷阱2：强行使用OmName或者OmLongName转为VsString指针去获取数据库VsString对象值，强转的VsString对象指针值指向的是未知地址，使用这个地址是危险的。
* 陷阱3：使用OmNameNew创建一个数据库对象VsString成员，如果保存长度超过32位的字符，则会动态分配内存，变为形式2，下次打开在OmIoName中解码VsString对象，由于指针指向的地址已失效（已不是保存前那个进程），字符串丢失，这是轻微的，继续向这块不可知地址中写数据，要么非法访问死机，要么造成内存破坏。
* 陷阱4：同3类似，使用OmNameNew创建一个数据库对象VsString成员，初始时保存少于32位的字符（这相当于形式1，不会造成问题），但在命令过程中使用OmNameSet更改为形式2，保存文件后再次使用会和3出现相同问题。
* 陷阱5：数据库对象确实是OmNameCreate创建的，但初始情况保存的少于32位的字符串，即形式1，后续在更改数据库对象的接口中（CdXXXVariable,CdXXXGetName等）使用OmNameSet或者OmNameCpy误将数据库的VsString对象改为形式1。从而会出现陷阱3情况。
陷阱（缺陷）6：VsString指向的数据库对象字符串指针失效，这种失效有VsString指向的VSTRING对象data没有swap 进来造成，也有VSTRING对象在内存中被更改造成。没有直接使用OmNameGet获取VsString成员ptr指向的地址来使用，造成非法访问死机或者文件破坏。

VsString缺陷
如果说上述的前五条为陷阱，我们通过正确的使用尚且可以避免，那陷阱6算的上是个缺陷了！为什么呢？起初发现陷阱6造成的问题时，我走查了所有的数据库对象Revise方法，确保每个从文件中加载的数据库VsString对象都调用了OmNameUpdate方法，但还是遇到了诸如组件丢失（组件引用零件名的使用是VsString）等一些死机报告问题。因为平台Om模块会在内存使用一定值后自动释放数据库对象空间（该开关默认开启），从而造成VsString指向的VSTRING对象数据被swap out出去，而代码中全然不知。第二种情形，平台Bin的blk_list分为稀疏和非稀疏两种，稀疏的blk_list在OmBinExpand后会扩容，造成已存在的对象失效，详情参考VsObjHandle失效。

应对方案：
* 针对陷阱1，平台定义了VX::AutoString 类，在需要使用VsString的地方（多数为传参），用VX::AutoString 的对象去传参，可以自动管理内存。
* 针对陷阱2，如果确定已有变量内存足够容纳要存储的VsString字符串，可使用OmNameProxy来构造VsSring对象或者使用C_AUTO_STRING（针对数组名）、C_AUTO_STRING_S（针对指针）构造VX::AutoString来获取对象。
* 针对陷阱3.4.5, 数据库VsString对象必须使用OmNameCreate,OmNameModify,OmNameDelete来进行创建，修改删除，其他接口一律不要使用。命令过程中的VsString对象一定不要用数库对象的接口，且尽量使用VX::AutoString包一层使用
* 针对陷阱6 ,Phil在Om自动释放数据库内存时做了限制，VsString对象不会被释放，从而减少了一些数据VsObjHandle失效的情形。Wiki在VsObjHandle失效中提到了稀疏blk_lis解决方案，现阶段我们需要在所有获取数据库VsString对象前调用OmNameUpdate更新字符串指针，主要是CdXXXVariable，CdXXXGetName，CdXXXRevise等接口，可以参考下面CdPartGetName的使用方式。虽然这会造成大量的OmNameUpdate代码，甚至会影响效率，但在彻底解决VsObjHandle运行中失效之前这是有意义的。
* 为发现VsString数据库对象错误使用的情况，在OmIoName中Encode VsString时，一旦发现错误形式立即报错，从而杜绝开发人员错误的用法；其次为避免已存在问题的文件造成新的问题，同时在OmIoName的DeCode时针对type为1的字符串，做清空处理，字符已丢但不能引起崩溃。

    
```c++
static int CdPartGetName
(
VsObjHandle *prtoh,  /* I: object handle */
VsObjMsg *msg     /* I: object message */
)
/*
DESCRIPTION:
Put a copy of the specified object's name (null-terminated ascii string)
in the memory referenced by "msg->out".  It is assumed "msg->out" references
enough memory to hold the object name.  If the object doesn't have a name,
no modifications are made to the input memory.

If "msg->in != NULL", set the object name to the null-terminated ascii name
referenced by "msg->in".

Return 1 if error, else 0.
*/
{
VLoadPart_Bin((VsObjBin*)msg->bin, prtoh, oh, obj, err);
if (err) return 1;

if (msg->in)
 {
 if (OmDocObjChkAndTouch((VsObjDoc*)(msg->doc), (VsObjBin*)(msg->bin), oh, VPART)==0)
  {
  OmNameModify((VsObjDoc*)(msg->doc), (VsObjBin*)(msg->bin), &obj->private_name, (const char *)msg->in);
  }
 }
else
 {
 if (OmNameUpdate((VsObjBin*)(msg->bin), &obj->private_name) == 0)
  {
  OmNameCpy((VsString*)msg->out, &obj->private_name);
  }
 }

return(err);
}
```

请注意，所有CdXXXGetName设置值时，传入的char*字符串，获取值时是用VsString对象，因为用void指针传递参数，切记上层不要使用错。直到安全的OmObjVarGet/OmObjVarSet工作完成。

总结

VsString造成的问题多数隐晦，难以发现，因为多数情况下，我们存储的字符都少于32位，错误使用接口不会立即造成问题。但这种错误一旦写进图纸，后果就不堪设想了。请大家一定要小心使用VsString的接口！！！

数据库的VsString对象类型（所有以private_XXX命名的数据库对象成员）只使用OmNameCreate,OmNameModify,OmNameDelete，OmNameGet
命令过程中的VsString成员（非形式3使用定代理VsString）使用OmNameNew，OmNameSet，OmNameCpy，OmNameDel，OmNameGet来操作，可以的话尽量使用VX::AutoString。
所有获取VsString数据库对象值的接口要OmNameUpdate。
使用一个非自身作用域的VsString对象一定要清楚它的来源和形式。














