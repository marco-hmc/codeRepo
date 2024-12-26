 文章题目	《模板命令开发流程》	 文章难度	
 题目描述	讲解模板命令的开发流程，介绍相关注意事项，分享相关经验讲解模板命令的开发流程，介绍相关注意事项，分享相关经验	出题信息	

出题人：

时间：2022.09 


 历史记录	




版本	修订人	修订日期	

 修订描述



	吴展新	2024.1.5	初稿

	
	
	


	
	
	





	 文章状态	




  已选题   

  撰写中

  审查中

  已完成

一、文档指引

本文将概括性地讲解模板命令的概念，指出相关的注意事项，并编写一个示例来演示模板命令开发流程，主要面向初学者。对于进阶知识，不作深入探讨，如有必要的，则附上相关文档链接。

二、模板命令概述

一般来说，当我们开发的功能需要与绘图区交互时，就需要使用模板命令。

”绘图区交互“指：

预览显示（Echo）；
拾取物体（Pick）；
动态拖拽（DDD）；

Echo：预览。echo这个单词本身的意思是“回声”。当命令被确认之前，我们可以先根据用户输入的参数创建临时的“幻象”显示在绘图区，这便是echo。

Pick：拾取。使用鼠标在绘图区上面移动或点击，可以对实体进行拾取。这里所说的实体，包括面、边、线、点等等。注意，并不是一定要发生“鼠标点击”才算是pick，鼠标在绘图区上面移动并触发实体高亮的过程，实际上就是在进行pick了。

DDD：动态拖拽标注（Dynamic drag dimension），是一种可以直接在绘图区上进行拖拽交互的标注。详细请参考《动态拖拽标注(DDD)开发指引》

2.1 模板命令简介

模板命令的开发包括以下步骤：

编写tcmd文件
制作ui文件（非必须）
编写cpp文件
修改zcui资源配置文件
2.1.1 模板命令启动方式
启动方式	附图
通过点击Ribbon栏上的按钮启动	


通过弹出菜单启动	


通过界面右下角的文本输入框启动	

以上为几种常见的模板命令启动方式。

2.1.2 模板命令的UI界面

以FtAllBox命令面板为例，如上图所示，红色框部分是FtAllBox.ui定义的Form，它的外面还套了一层Form，叫做InputManager。

可以看到InputManager除了包裹模板命令窗体之外，还提供了OK按钮、Cancel按钮、Apply按钮、Help按钮以及Dock/UnDock按钮。

2.1.3 关于模板命令的对象化理解

我们可以把模板命令理解为一个对象：

tcmd中配置的是这个对象的各个参数（又称作字段field）。
每个参数都可以与VDATA（数据）关联。ui控件通过与tcmd的参数绑定，可以实现与VDATA的间接关联。（后文将对VDATA作解释）
参数有多种类型。不同类型的参数可以关联不同类型的VDATA。
参数还有许多属性配置。通过属性配置，参数可以实现更丰富的功能。
2.1.4 关于模板命令与指令的关系理解

模板命令是通过指令触发的。指令是ZW3D实现功能调用的机制。关于指令系统，可查阅《指令管道介绍》。

有了指令，模板命令就可以通过以下两种方式启动：（1）通过点击Ribbon栏上的按钮启动；（2）在ZW3D界面右下角输入“!XXXXX”（比如!FtAllBox）。

为了让模板命令可以通过指令触发，需要修改zcui资源配置文件。

2.1.5 关于模板命令的其他理解

模板命令是我们开发ZW3D功能的一种方式。

模板命令也是ZW3D历史的一种体现，它依然保留着不少C语言的开发方式，这个框架在未来很可能无法满足我们新功能的开发（笔者个人见解）。




接下来，本教程先对模板命令开发中的涉及的每种文件做简要介绍，然后在后续的章节中对开发步骤进行详细说明。

2.2 ui文件简介

.ui文件记录了窗体、控件、布局等信息。我们可以使用Qt Designer来创建或修改.ui文件，后文会介绍详细的配置过程。

其实模板命令不需要ui面板也能运行，是否要创建.ui文件取决于具体的业务需求。当然，大部分模板命令都配有对应的ui面板。

针对ui，我们只需要关注以下两点（1）如何让ui控件与tcmd参数产生关联；（2）如何在cpp中调用接口来操控ui控件。后文会对这两点做详细讲解。

在Qt Designer左侧边栏可以看到，有ZW3D的扩展控件ZW3D Template Widgets和ZW3D Widgets。前者又称为“模板控件”，后者又称为“非模板控件”。

如果侧边栏没有这些控件，说明插件未正常加载，解决方法参考ZW3D Qt Designer插件部署

如果控件需要与VDATA关联，则必须使用ZW3D Template Widgets，而不能使用ZW3D Widgets。关于VDATA的解释，以及控件是如何与VDATA关联的，将在后文详细描述。

2.3 tcmd文件简介

tcmd实际上是一个xml文件。

<?xml version="1.0" encoding="UTF-8"?>
<templates xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="../schemas/Template.xsd">
    <template name="FtAllExt">
		<property name="icon_id">11</property>
	 	<property name="function">FtAllExt</property>
		<parameters>
	    	<parameter luid="14" description="Combine method" type="option">
                <property name="options">@sym_int=0,|enable=FtBoolHasShape,|auto_log,|reactivate,|echo_at_last</property>
                <property name="callback">FtAllExtCb</property>
           	 </parameter>
			<!-- ...... -->
            <parameter luid="31" description="Extrude type" type="option">
                <property name="options">@sym_int=1,|auto_log,</property>
                <property name="callback">FtAllExtSkip</property>
            </parameter>
		</parameters>
		<!-- XXX is stored in field 9 -->
	</template>
</templates>

tcmd由（1）template、（2）template的property、（3）parameter以及（4）parameter的property，共4个部分组成。

同一个tcmd文件可以定义多个template，只需将它们都包含在<templates></templates>中即可。（比如CdDst2All.tcmd，就定义了CdDst2All和CdDst2AllChld两个模板命令。）

2.3.1 template（模板）配置

模板命令之所以被称为“模板”命令，是因为它的配置都遵循同一套模板，并且每个命令的具体定义都被包含在<template></template>中。（笔者个人推测）

template字段用于配置模板命令的名称。

template的property则用于该模板的各种属性以及各种回调函数。

参考资料：

《模板命令回调机制》
tcmd文件及字段介绍（日常积累版）
2.3.2 parameter（参数）配置

我们也用field（字段/域）来形容参数。在tcmd中，通过luid来配置参数的id，在.cpp编码中我们又会将其称作fieldId。虽然名称有很多种，但意思都一样。

参数类型：

参数类型决定了其关联VDATA的类型，也决定了ui应该选择什么类型的控件。

parameter type	enum VeCdWiClass	适用Ui控件
"null"	 VIN_NULL	无
"string"	VIN_STR	

ZsCc::String

ZsCc::FormProxy (InBrowser的特殊用法)


"number"	VIN_NUM	

ZsCc::Number

ZsCc::Slider

ZsCc::Color

ZsCc::ColorTransfer


"distance"	VIN_DST	ZsCc::Distance
"angle"	VIN_ANG	ZsCc::Angle
"point"	VIN_PNT	

ZsCc::Point

ZsCc::Entity

ZsCc::Pick

ZsCc::PickList


"entity"	VIN_ENT	

ZsCc::Entity

ZsCc::EntityList

ZsCc::EntityTable

ZsCc::Pick

ZsCc::PickList

ZsCc::FormProxy (InBrowser的特殊用法)


"option"	VIN_OPT	

ZsCc::OptionButtons

ZsCc::OptionCheckBox

ZsCc::OptionCombobox

ZsCc::OptionRadios

ZsCc::DrawbackBoxGroup (但一般不会这样用)


"continue"	VIN_CONT	无
"form"	VIN_FORM	ZsCc::FormProxy
"window"	VIN_WIN	ZsCc::Window
"command"	VIN_CMD	ZsCc::CmdButton
"pin"	VIN_PIN	

ZsCc::PinEntity

ZsCc::PinEntityList


"optgroup"	VIN_OPTGROUP	ZsCc::DrawbackBoxGroup
"number_unit"	VIN_NUMUNIT	ZsCc::NumberUnit
"custom_input"	VIN_CUSTOMINPUT	自定义

当参数修改了VDATA中的数据后，会通知ui控件更新数据（需要主动调用接口InOptFormSetVal()）。当ui输入了新数据后，会将数据传递给参数中的VDATA。

关于哪种参数应该与哪种控件绑定，可参考ZsDi::Binder的派生类重写的bind()方法。

关于参数与控件的数据绑定关系见MVC一文。

参考资料：

参数配置是tcmd编写中最重要的一环，ZW3D在多年的发展中，定义了越来越多的参数字段，其中options参数的字段就非常多。比较遗憾的是，目前为止还未能有一份文档能够充分地整理所有的字段。

以下资料是对各种字段的整理和总结。

《Tcmd关键字解析》
tcmd参数字段介绍（日常积累版）
tcmd参数option字段介绍（日常积累版）
Pick相关TCMD参数管理
《使用Tcmd编辑器进行tcmd设计指引》
2.3.3 parameter（参数）跳转机制

当一个参数获得输入数据，并确认后，命令系统会自动跳转到下一个参数。参数的跳转顺序并不是由ui控件的前后顺序决定，而是由tcmd中parameter的顺序决定。

有些参数收到输入后会自动确认；有些则需要用户按键盘Enter或者鼠标中键进行确认。

一个理想的模板命令运行流程：用户打开模板命令后，命令系统自动激活第一个参数，用户输入数据，然后命令系统自动跳转到下一个，用户继续输入，直至完成所有的参数输入，完成命令。

参数跳转机制提高了模板命令的易用性，使用户能够更轻松地输入参数。

参考资料：

《模板命令参数跳转机制》
2.4 VDATA和DB简介

模板命令参数的实际数据叫做VDATA。当模板命令被实例化的时候，会在数据库创建一个VIDX_LIST对象，该对象实际上就是一个数组，存储着我们的字段对应的VDATA的索引，即数组本身并不存储实际数据，而是存储索引。我们通过索引去访问VDATA。

VDATA是一个泛称，指代数据库中的数据。开头的“V”源自Vx。enum VeCdClass、enum VeOmClass定义了VDATA的具体类型。

DB是Database的缩写，代指数据库。这里的数据库并不是指我们常见的关系型数据库或非关系型数据库。在ZW3D中，数据库可以直接理解为”存数据的一块内存空间“。数据库模块定义了”Bin“概念来形容这种内存空间。

BIN的种类由enum VeTargBin定义，对于模板命令的开发，我们大多数情况只需关注PRJ_BIN和TRG_BIN即可。数据库系统的惯用定义：PRJ_BIN用来存储临时数据，TRG_BIN用来存储持久化数据。

参考资料：

《OM/DB的常见概念及全局变量介绍》

在Visual Studio中使用ZW3D插件查看VDATA：

先运行ZW3D，打开Block命令，输入一些参数。我们可以在其Echo回调FtAllBoxEO()中打个断点，稍微修改一下参数就能触发该Echo回调。

在Vs的文本编辑区双击某个变量名，比如我们双击idxIn

然后在菜单栏中 Extensions → ZW3D → View VsObject(PRJ_BIN)

然后我们就能在Watch窗口中查看PRJ_BIN中对应VsObject的数据。

当然也可以直接在Watch中输入 (((ZW3D_Om.dll!VgOm)->prj)->blk_list + ((idxIn)/512))→obj[(idxIn)%512]

（1）将idxIn修改成具体的数字，则可以查看不同数据库对象的信息；

（2）将prj改成trg可以查看TRG_BIN中的数据。

展开data可以查看其具体数据。对于这里的VIDX_LIST对象，就如前文所说，它的data其实就是一个数组，存储着其他VDATA的索引。

-9表示对应的参数还未初始化或未被使用。

假如我们想查看field2的数据，则在Watch中输入 (((ZW3D_Om.dll!VgOm)->prj)->blk_list + ((189)/512))→obj[(189)%512]

可以看到PRJ_BIN索引189下存储的数据是一个VPNT3对象。

2.5 简介总览

以FtAllBox为例，概括ui控件、tcmd参数、VDATA、DB之间的关系：

【模板命令总览，参考自模板命令的评论区】

三、开发模板命令的流程

接下来，我们将展示一下开发模板命令的简单流程。

为了让示例更丰富，我决定做一个”猜数字“的游戏。模板命令的需求定义如下：

命令在初始化的时候随机生成两个数值，分别表示最小值和最大值。玩家需要输入正确的数值才能成功执行命令。
定义两个点类型参数。玩家输入两个点可以生成一条线段，这条线段长度就代表玩家输入的”数值“。
若线段长度不符合最小值和最大值的限定，则无法通过，命令执行失败；若符合限定，则通过，命令执行成功。
为了游戏降低难度，ui面板中再增加一个控件用来显示最小值和最大值的范围。
3.1 模板命令命名

关于模板命令的命名，可以参考现有命令，比如圆倒角命令叫做FtFillet（Ft表示Ftr，Feature），圆线框命令叫做CdWrCircles（Cd表示Cad，Wr表示Wireframe）。

命令名的用途：

用于确定指令名。模板命令需要通过指令系统来启动，而所有的指令都是由字符串转换而来（至少目前是这样）。模板命令对应的指令类型是FormCommand，其字符串命名以感叹号为前缀，如!FtAllBox，!CdWrCircles。查阅《指令管道介绍》可了解更多指令相关知识。
用于确定各种回调函数的命名。比如FtAllExt命令，它的求值回调叫做FtAllExt，Echo回调叫FtAllExtEO，init回调叫FtBaseExtInit。

命令名在过去有长度限制，最长只能有16个字符。2023年底的一次重构去除了该限制，但为了命令易用性，建议大家尽量将命名限制在20个字符以内。

在ZW3D右下角控制台输入命令$report，可以实时输出调试信息。随后我们打开命令的时候就可以看到它的命令名。

由于本教程仅作示例，我决定为这个模板命令套用一个风靡全球的国产游戏的名字——Genshin。

3.2 创建ui文件

打开Qt Designer，在菜单栏File→New新建ui文件。选择ZW3D OptionForm，点击Create。（OptionForm是模板命令窗口在Ui层的名称）

模板命令窗口的主体一个ZsCc::DrawbackBoxGroup控件，ZsCc::DrawbackBoxGroup由一个一个ZsCc::DrawbackBox组成。双击DrawbackBoxGroup可以编辑DrawbackBox。

在我的例子中，只需要一个DrawbackBoxGroup就够了，所以我把其余两个Box都删了。然后往上面添加了两个QLable和两个ZsCc::Point。

3.2.1 控件命名规范
注意，我们需要对控件进行重命名，将控件命名为 id? 的形式，将与其配对的QLable命名为 id?label 的形式。
然后还要对ZsCc::Form进行重命名，修改为我们的模板命令名。

3.2.2 配置id

然后我们需要编辑两个ZsCc::Point的Dynamic Properties，为其添加id属性（默认已经自带了），然后将值修改为其对应的id值。

          

3.2.3 布局优化

可以发现，我们模板命令每一行都是由【QLabel+输入控件】的形式组成，大多数模板命令都是这样。

我们一般规定Label和输入控件在水平布局方向上的空间占比为1:2。

选择布局所在的控件page_0，然后在 Property Editor 中编辑 layoutColumnStretch 的值为“1,2”。

          

1:2的水平布局的比例：

3.2.4 保存文件

最后保存文件到目录 C:\ZW3D\Source\driver\forms\ 下，以模板命令名作为文件名。

3.3 编写tcmd文件

在 C:\ZW3D\Source\driver\commands\ 目录下新建.tcmd文件，以模板命令名为文件名。

<?xml version="1.0" encoding="UTF-8"?>
<templates xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="../schemas/Template.xsd">
    <template name="Genshin">
        <property name="function">Genshin</property>
        <property name="echo_obj">GenshinEO</property>
        <property name="init">GenshinInit</property>
        <property name="init_after">GenshinInitAft</property>
        <parameters>
            <parameter luid="1" description="1st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a start point of the line.</property>
            </parameter>
            <parameter luid="2" description="2st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a end point of the line.</property>
            </parameter>
            <parameter trigger="true" luid="6" type="continue">
                <property name="prompt">&lt;middle-click&gt; to finish.</property>
            </parameter>
            <parameter luid="3" description="Limitation" type="string">
                <property name="prompt">The length limit of the line.</property>
            </parameter>
            <parameter luid="4" description="Minimum length" type="number">
            </parameter>
            <parameter luid="5" description="Maximum length" type="number">
            </parameter>
        </parameters>
    </template>
</templates>


在tcmd中，我们配置了命令的名称，命令的执行函数名（求值函数）Genshin，Echo回调函数名GenshinEO，init回调函数名GenshinInit，init_after回调函数名GenshinInitAft。

然后我们还配置了几个字段，其中两个为point字段用于接收用户的点输入；一个string字段用于显示提示信息；两个number字段用于表示线段的最小值和最大值；还有一个trigger为true的continue字段，该字段将在后文的“tcmd进阶”章节介绍。

可以看到，我们为parameter配置了property。在上面的例子中，为id1配置了options property和prompt property。

options可以配置一段字符串，在参数加载的时候，这段字符串会被CdWiXXXOpt()解析。比如id1中配置了/face/edge/curve/point/，这表示实体过滤器，限制该point字段可以pick面、边、曲线和点。另外还配置了ddd_drag，表示这个point可以被拖拽。
prompt也是配置一段字符串，将作为该字段的提示词。需要注意的是，这里的字符串会被作为翻译资源提取，因此英文语法要正确。见资源代码规范。
3.4 修改zcui资源配置文件

为了使我们的命令可以被调用，还需要将它添加到Actions.zcui和Scenes.xml中。

关于更详细资源配置，如菜单配置、角色配置等，则需要修改PopupMenus.zcui、Roles.zcui等配置文件。详情可查阅《UI资源配置加载及架构》

使用Everything或者VsCode的Ctrl+P可以快速搜索文件。

3.4.1 配置Actions.zcui

目前，ZW3D绝大部分行为都是通过指令触发的。为了能够触发指令，我们使用了Qt的QAction机制，将QAction与指令相互关联。而QAction可以被绑定在按钮控件（Button）和菜单项（Menu）上面。这样我们点击按钮或菜单项，就可以触发指令了。

指令模块定义了class ZsCs::Action，继承自QAction，作为ZW3D的自定义Action类。Actions.zcui则是记录了Action的配置。

<?xml version="1.0" encoding="UTF-8"?>
<Actions system="true">
	<!-- ...... -->
	<Action name="ID_!Genshin" type="button">
		<Form>Genshin</Form>
		<Text>
			<Ribbon>Genshin</Ribbon>
			<Menu></Menu>
		</Text>
		<Icon>ICON12345</Icon>
		<Hint>Genshin Impact, Qi Dong!</Hint>
		<Help></Help>
		<Desc>A game about guessing number. Player inputs two point to create a line. If the length of the line satisfies the limit number, game passed, otherwise game failed.</Desc>
		<Script>!Genshin</Script>
		<Condition></Condition>
	</Action>
</Actions>

字段解释

Action的name字段，表示Action的名称，type字段表示Action关联的ui类型，一般都是"button"
Form字段，表示.ui的名称
Text字段，表示该Action在Ribbon栏和菜单栏显示的文本。若不需要在Ribbon栏或Menu中显示，则可以不配置。
Icon字段，表示该Action对应的icon图片资源名称，一般都是.png文件，在这里配置时不需要加上.png后缀。icon资源存放在 C:\ZW3D\Source\driver\icons 目录下。icon图片由产品同事提供。
Hint字段，表示该Action的提示词。鼠标悬停在按钮上的时候会显示。
Help字段，表示帮助提示词？笔者也不清楚，因为绝大部分Action都没有配置，并且少有的配置了该字段的ID_!CdChamfer，也没有看到Help字段在哪里显示了。
Desc字段，表示Action的的详细提示词。鼠标悬停在按钮上间隔较久的时候就会显示。
Script字段，表示Action关联的指令名。
Condition字段，表示什么情况下该Action可以被执行。用法：<Condition>customFn=CdInqStockIsRunning</Condition>，当函数CdInqStockIsRunning返回1的时候，action才允许被执行。

由于本教程制作的模板命令仅作示例，因此icon由我们自己画，icon大小为64x64像素。当然更方便的方法是直接套用其他命令的icon。

3.4.2 配置RibbonPages.zcui（可选）

为了能让我们的模板命令出现在Ribbon栏上，需要将Action添加到RibbonPages.zcui中。

由于本教程的命令仅作示例，为了方便寻找，打算直接添加到Block命令旁边：

<RibbonPages>
	<!-- ...... -->
	<RibbonPage name="UiFtrTool" text="Shape" visible="true">
		<!-- ...... -->
		<RibbonGroup name="BasicShapes" text="Basic Shape" visible="true">
			<GroupPanel name="BasicShapes_GroupPanel">
				<!-- ...... -->
				<ControlMenu name="ID_!FtAllBox#Menu" defaultAction="ID_!FtAllBox" visible="true" buttonStyle="4">
					<Item action="ID_!FtAllBox" visible="true" />
					<Item action="ID_!Genshin" visible="true" />
					<Item action="ID_!FtAllCyl" visible="true" />
					<!-- ...... -->
				</ControlMenu>
				<!-- ...... -->
			</GroupPanel>
			<!-- ...... -->
		</RibbonGroup>
		<!-- ...... -->
	</RibbonPage>
	<!-- ...... -->
</RibbonPages>

效果预览：

3.4.3 配置Scenes.xml

命令有“场景化”的概念。ZW3D有多种场景，如Part、Assembly、Part/Assembly、Sketch、Sheet、Cam等。命令应该被限定在特定的环境中使用。比如属于Cam的哪些命令，总不能在Part中启动吧？

Scenes.xml中记录了每个场景下可以执行的命令。

本教程的示例命令只需要在Part场景下运行，因此在Scenes.xml的Part场景（注意不是Part/Assembly）下添加我们命令对应的Action名。

<?xml version="1.0" encoding="UTF-8"?>
<Scenes>
	 <!-- ...... -->
	<Scene name="Part" white="true">
		<!-- ...... -->
		<Command action="ID_!Genshin"/>
    </Scene>
	<!-- ...... -->
</Scenes>

关于场景化的详细介绍，可查阅《Scene场景/命令场景化的介绍与配置》

3.5 cpp编码
3.5.1 注册命令和函数定义

本教程的模板命令仅作示例，因此.cpp文件创建在 C:\ZW3D\Source\cad\src\cmd\debug\ 目录下。在实际的开发中，请根据命令的功能定义，将代码文件放在对应的模块下。

在上述目录创建Genshin.cpp文件。对于cpp中的内容，可以复制现有模板命令，如FtAllBox.cpp，注意将命令名替换成自己的模板命令。

编码规范见 ZW3D编码规范。

本教程作为示例，为了精简，部分代码不会完全符合规范。在真实开发场景中，请务必遵守规范！

下面的代码，首先调用VmRegisterFile()，VmRegisterTemplate()等MACRO来注册模板命令。其中需要注意是VmRegisterTemplate()的最后一个参数，与License有关，实际开发时请根据项目实际情况来决定输入什么参数。这里为作示例，直接使用了ZW_ANY_PRODUCT。

/**
**   (C) Copyright 2024, ZWSOFT Co., LTD.(Guangzhou) All Rights Reserved.
*/

VmRegisterFile(Genshin);
VmRegisterTemplate(Genshin, Genshin, ZW_ANY_PRODUCT);
VmRegisterEchOFunction(Genshin, GenshinEO);
VmRegisterInitFunction(Genshin, GenshinInit);
VmRegisterInitafterFunction(Genshin, GenshinInitAft);

#define V_FLD_PNT1 1
#define V_FLD_PNT2 2
#define V_FLD_LIMIT_STR 3
#define V_FLD_MIN_LENGTH 4
#define V_FLD_MAX_LENGTH 5 

/*******************************************************************/
/* PRIVATE */
static int Genshin
(
int idx_in,
int *idx_out
)
{
    return 0;
}

/*******************************************************************/
/* PRIVATE */
static void GenshinEO
(
int idx_in,
VsObjHandle *oh_echo
)
{
}

/*******************************************************************/
/* PRIVATE */
static void GenshinInit
(
int idx_in
)
{
}

/*******************************************************************/
/* PRIVATE */
static int GenshinInitAft
(
int idx_in
)
{
    return 0;
}




注意，还需要将.cpp添加到对应模块的CMakeLists.txt中。（注意按字母顺序排序）




...
zw_target_sources(
    ${PROJECT_NAME} PRIVATE
    "global/VxCadGlobal.cpp"
    "pch/Cad.cpp"
    "pch/CadCPP.cpp"
    "src/VxCadPub.cpp"
	...
	"src/cmd/debug/Genshin.cpp"
	...
)
...




为了使我们的.cpp编译单元可以被链接，还需要在DiForceSymRef.cpp做如下配置：（注意按字母顺序排序）

ZmForceSymRef(Genshin);




3.5.2 template回调函数编码（功能实现）

目前我们的Field1和Field2都能正常获取点输入了，但绘图区并没有显示Echo预览，Field3的控件也没有显示内容。所以接下来我们要完善各个回调函数，实现我们想要的功能。

首先，为了显示预览，需要在Echo回调中读取field 1和field 2两个point，然后以此调用CdLine3Create()接口创建VsLine对象，接着调用CdObjAddTo将VsLine对象添加到Echo对象中。这样便能显示我们的线段了。

从字段VDATA读取数据的接口，一般都命名为VxInpXXX()；往字段VDATA写入数据的接口，一般都命名为VxLogXXX()。

VsObjHandle表示对象句柄，通过它可以方便地访问Bin中的对象。

需要注意的是，这里创建的VsLine对象只是用作预览，属于临时数据。前文已提到，我们的开发规范是将临时数据存放到PRJ_BIN中。因此在调用CdLine3Create()之前，需要先调用C_AUTO_REVERT_BIN_INIT()，将bin切换至PRJ_BIN。

/*******************************************************************/
/* PRIVATE */
static void GenshinEO
(
int idx_in,
VsObjHandle *oh_echo
)
{
    int iErr = 0;
    VsPoint start_pnt = {};
    VsPoint end_pnt = {};

    if (iErr = Loc_GetInputPoint(idx_in, &start_pnt, &end_pnt))
        return;

    VsObjHandle ohLine;
    VsLine zLn = {start_pnt, end_pnt};

    {
        C_AUTO_REVERT_BIN_INIT(PRJ_BIN);
        if (iErr = CdLine3Create(&zLn, &VgCdEchoAt, &ohLine))
            return;
        if (iErr = CdObjAddTo(&ohLine, oh_echo))
            return;
    }
}

/*******************************************************************/
/* PRIVATE */
static int Loc_GetInputPoint
(
int idx_in,
VsPoint *start_pnt,
VsPoint *end_pnt
)
{
    if (!start_pnt || !end_pnt)
    {
        zwAssert(zwlog_cad, false);
        return 1;
    }
    /* Get start point */
    if (VxInpPnt(idx_in, V_FLD_PNT1, 3, reinterpret_cast<double *>(start_pnt)))
        return 1;
    /* Get end point */
    if (VxInpPnt(idx_in, V_FLD_PNT2, 3, reinterpret_cast<double *>(end_pnt)))
        return 1;
    return 0;
}

我们的“猜数游戏”机制还未完成，前文提到，在命令初始化的时候，需要生成两个随机数作为最小值和最大值，只有当我们创建的线长度刚好处于这两个值之间时，才算通关。

为此，我们需要在init回调中初始化最小值和最大值，记录在fld4和fld5中，然后在init_after回调中再读取出来，更新ui，显示提示信息。

注意，init回调执行的时候，UI界面还未初始化，因此还不能调用UI相关接口。如果要进行UI相关的初始化操作，则应该写在init_after回调中。更多回调函数注意事项见《模板命令回调机制》。




/*******************************************************************/
/* PRIVATE */
static void Loc_GenerateRandomNumber
(
double *pMinValue,
double *pMaxValue
)
{
    if (!pMaxValue || !pMinValue)
    {
        zwAssert(zwlog_cad, false);
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(50.0, 100.0);
    double minValue = dis(gen);
    double maxValue = dis(gen);
    if (VxDoubleGreaterThan(minValue, maxValue))
    {
        std::swap(minValue, maxValue);
    }

    *pMinValue = minValue;
    *pMaxValue = maxValue;
}

/*******************************************************************/
/* PRIVATE */
static void GenshinInit
(
int idx_in
)
{
    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min) || VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
    {
        /* Doesn't get value from fld4 and fld5 successfully, so it means there are not data.*/
        Loc_GenerateRandomNumber(&limit.min, &limit.max);
        if (VxLogNum(idx_in, V_FLD_MIN_LENGTH, V_NUM, limit.min))
            return;
        if (VxLogNum(idx_in, V_FLD_MAX_LENGTH, V_NUM, limit.max))
            return;
    }
}

/*******************************************************************/
/* PRIVATE */
static int GenshinInitAft
(
int idx_in
)
{
    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min))
        return 1;
    if (VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
        return 1;

    std::stringstream ss;
    ss << limit.min << "mm ~ " << limit.max << "mm"; // assume the unit is "mm"
    if (VxLogStr(idx_in, V_FLD_LIMIT_STR, ss.str().c_str()))
        return 1;
    (void)InOptFormSetVal(V_FLD_LIMIT_STR, V_FALSE);
    return 0;
}

最后，编写模板命令的求值回调，在这里决定“游戏”是否能通关。

/*******************************************************************/
/* PRIVATE */
static int Genshin
(
int idx_in,
int *idx_out
)
{
    VsPoint start_pnt = {};
    VsPoint end_pnt = {};
    if (Loc_GetInputPoint(idx_in, &start_pnt, &end_pnt))
        return 1;

    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min))
        return 1;
    if (VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
        return 1;

    if (!Loc_ValidateLineLength(start_pnt, end_pnt, limit))
    {
        zwAlert(zwlog_cad) << "The length of the line doesn't satisfy the answer.";
        return 1;
    }

    return 0;
}

/*******************************************************************/
/* PRIVATE */
static bool Loc_ValidateLineLength
(
const VsPoint &p1,
const VsPoint &p2,
const VsLim1 &limit
)
{
    double input = std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2);
    double min = std::pow(limit.min, 2);
    double max = std::pow(limit.max, 2);
    if (VxDoubleGreaterThan(input, min) && VxDoubleLessThan(input, max))
    {
        return true;
    }
    return false;
}




3.5.3 parameter回调编码（功能优化）

目前游戏难度还是太高了。因此我又加了一个控件，用于显示一块颜色，当颜色趋于红色的时候表示答案错误，当颜色趋于绿色的时候表示答案正确。

先往ui窗体中添加了一个ZsCc::ColorPicker控件，注意该控件不是模板控件，不能与VDATA绑定了。我们现在只是想用它来显示颜色，所以影响不大。

将ZsCc::ColorPicker的type属性设为0，表示使用真彩色。将id设为7，以便可以在代码中通过接口来访问。

然后在tcmd中，要做两件事情：

为fld1和fld2添加callback属性，配置回调函数。callback会在当前参数发生改变时触发。对于point参数，当发生pick、unpick、拖拽等都会导致参数的值发生变化。
id7控件不需要绑定VDATA，因此我们不需要新增字段，但我们还是应该在后面写上一段注释，表示field 7已经被保留，防止以后弄错。
<?xml version="1.0" encoding="UTF-8"?>
<templates xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="../schemas/Template.xsd">
    <template name="Genshin">
		<parameters>
            <parameter luid="1" description="1st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a start point of the line.</property>
                <property name="callback">GenshinPointCb</property>
            </parameter>
            <parameter luid="2" description="2st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a end point of the line.</property>
                <property name="callback">GenshinPointCb</property>
            </parameter>
			<!-- ...... -->
        </parameters>
        <!-- Field = 7 reserved for color -->
    </template>
</templates>

效果如下，当线段长度不符合限定时，显示红色；当符合限定时，显示绿色。游戏难度大幅降低。

3.6 更新 (编译) 资源文件

（1）若在仓库中修改了已经存在的资源文件，则build一下zw3d（即Visual Studio按“F5”启动zw3d）即可应用修改。

（2）若在仓库中新增了资源文件（如.tcmd, .ui, .icons），则需要重新build一下ResourceSystem工程以重新生成cmake cache，从而触发qrc的产生和rcc的编译。

更多详情查阅：资源编译

3.7 效果展示

四、tcmd进阶
4.1 trigger

前文提到，在模板命令中，一个参数完成输入后就会自动跳转到下一个参数。若某个参数被设置为trigger，那么当它完成输入后就不再是跳转到下一个参数，而是直接触发命令确认（相当与点击OK按钮）。

大部分tcmd中，trigger不需要绑定控件，所以都是配置一个type="continue"的参数来作为trigger。当然有些tcmd也会用其他类型的参数来作为trigger，使输入操作更为流畅。（比如草图环境下的Point命令[!WrCrPtPop]）。

关于trigger的详细讲解，可查阅《模板命令参数跳转机制》。

4.2 multi_cmd

有些命令的功能会有多种模式，比如打孔命令（Hole），有4中打孔模式；倒角命令（Chamfer），有3种倒角方式。若每种模式都弄成单独的命令，那将非常冗余，因此需要有套机制使得我们可以在一个命令中开发多种模式。multi_cmd就是为了实现这个机制。

以命令FtHoleMain为例，multi_cmd属性配置方式如下：

    <template name="FtHoleMain">
        <property name="function">FtHoleMain</property>
        <property name="multi_cmd">
            6,
            0=|-201|-202|-62|-61|-40|-41|-168|-63|-167|-104|-105|,
            1=|-202|-62|-61|-40|-41|-168|-63|-167|-104|-105|-110|,
            2=|-201|-104|-105|,
            3=|6|3|19|74|90|2|20|75|104|105|203|,
        </property>
         <parameters>
            <parameter luid="6" description="Hole type" type="option">
                <property name="options">@sym_int=0,</property>
                <property name="callback">FtHoleAtCb</property>
            </parameter>

其中，6表示field 6，对应type="option"的参数，ui上一般对应ZsCc::OptionButtons控件。

后面接的”0=|-201|-202|-62|-61|-40|-41|-168|-63|-167|-104|-105|“ 表示一条pipe。其中0表示option的第0项对应的参数配置，等号后面接的是field id，每个field id用"|"进行分隔。在id前面添上减号"-"表示隐藏该字段。

multi_cmd的同一项配置中，不能出现正负数混用的情况，要么全写成正数，要么全写成负数。

若写成这样：3=|6|3|19|74|90|2|20|75|104|105|203|-2| 则会发生错误。

接着，还需要在.ui中对ZsCc::OptionButtons内部Button进行data属性的配置，使它们能够关联上对应的pipe。data以“序号:”的形式进行配置，比如第0个按钮的配置为0:，第1个按钮配置1:。




总结一下，multi_cmd其实就是一套对参数进行隐藏的机制，并且会确保每个pipe的参数跳转的正确性（见《模板命令参数跳转机制》）。

4.3 sym_xxx

命令符号变量，项目2600_CmdInitMgt_II引入的机制。

sym的全称是symbol。在模板命令机制中，规划了几个全局的symbol table（符号表）来存放参数的符号值。

由于模板命令并没有使用c++的类进行封装，为了实现某些功能，一些代码会将field值存放在全局变量中。但这导致存在这样的情况：同一命令的不同 field、不同命令的 field 共用一个变量的情况，导致它们互相干扰。

命令符号变量就是用于解决上述问题。

template <typename key1, typename key2, typename tp> class CmdTable
{};
typedef CmdTable<std::string, int, int> CmdIntTable;
typedef CmdTable<std::string, int, double> CmdDblTable;
typedef CmdTable<std::string, int, std::string> CmdStrTable;

符号表以 <命令名, field id>作为key。

在tcmd的parameter的options property中，使用 @sym_int=val、@sym_dbl=val、@sym_str="val" 来配置参数的符号变量的默认值。若省略val，对于sym_int和sym_dbl，自动以0为默认值；对于sym_str，自动以空字符串""为默认值。

            <parameter luid="35" description="Line type" type="option">
                <property name="options">@sym_int=0,~WrSmtInit,</property>
            </parameter>
            <parameter luid="8" description="Distance" type="number_unit">
                <property name="options">@sym_dbl=10.0,|unitType=distance,pop_up=AnimDstInp</property>
            </parameter>
            <parameter luid="28" description="Starting label" type="string">
                <property name="options">@sym_str="A",empty_ok,|enable=CdAnntTblLblEn,</property>
            </parameter>

详细用法以及注意事项见命令符号变量。

4.4 child

模板命令定义了parent-child关系，是一种”调度方式“。

给template配置child property，可以让该模板命令作为另一个模板命令的子命令。

    <template name="CdAngFace">
        <property name="function">CdAngFace</property>
        <property name="child">true</property>
        <parameters>
        </parameters>
    </template>

一般child命令会放在控件的popupMenu中。点击控件右边的小箭头按钮可以弹出popupMenu。

child命令被调用时，会把parent命令“挂起”；child命令确认后，会重新”唤醒“parent命令，并把数值返回到对应字段中。

   ----------》  

其他”调度方式“有：（1）辅助命令的”level=1“；（2）FormProxy的内嵌；（3）VxInput。（调度方式太多，导致代码混乱，开放难度增加。将来会考虑优化这些机制，降低控制命令调度开发的难度。）

相关资料：《模板命令调用方式介绍》

4.5 SetList

SetList是另一种关于模板命令parent-child关系的应用。

SetList分为Set和List两个部分：

Set对应的是type="form"的参数，控件对应ZsCc::FormProxy；
List对应的是type="entity"或者"point"的参数，控件对应ZsCc::Point、ZsCc::Entity、ZsCc::EntityList、ZsCc::EntityTable。

在tcmd中，set和list通过comp property相互关联，set参数要配置template property关联一个child模板命令。

    <template name="WrCrSpline">
        <property name="icon_id">15</property>
        <property name="function">CdWrCrSpline</property>
        <property name="echo_obj">CdWrCrSplineEO</property>
        <property name="term">CdWrCrSplineTerm</property>
        <property name="init_after">CdWrCrSplineInitAfter</property>
        <property name="multi_cmd">51,0=|-52|,1=|-9|-6|,</property>
        <parameters>
		     <parameter luid="20" description="Point" type="form">
                <property name="options">empty_ok,</property>
                <property name="comp">2</property>
                <property name="template">CdCvIntPnt</property>
            </parameter>
            <parameter luid="2" description="Point list" type="entity">
                <property name="options">empty_ok,</property>
                <property name="list">1</property>
                <property name="comp">20</property>
				<!-- ...... -->
            </parameter>

对于child模板命令CdCvIntPnt，需要配置属性child，表示它是一个child命令；还要配置属性parent_form，表示它将附属在一个parent form上面。

注意：若child命令有echo回调，那么命令系统在执行完它的echo之后，会接着去执行parent命令的echo，使用的是同一份echo对象。

    <template name="CdCvIntPnt">
        <property name="icon_id">15</property>
        <property name="function">CdCvIntPnt</property>
        <property name="child">true</property>
		<property name="parent_form">1</property>
		<property name="echo_obj">CdCvIntPntEchO</property>

SetList的UI效果：

关于SetList详细使用可查阅《Setlist功能介绍》

4.6 特征创建

模板命令的一大用途是用来创建特征。特征能保存模板命令的各个参数值，可用于表示建模的历史，是参数化建模的重要功能之一，是实现历史重定义、重生成、回滚等功能的基础。

特征的创建一般都是在模板命令的求值回调中进行。详情见《特征流程》。

模板命令求值的时候不一定非要创建特征，但特征的创建似乎总是要依赖模板命令的求值流程。目前InEvalErr中的代码耦合了不少特征相关的逻辑，后续需要对其进行优化。

4.7 Partial Echo

Partial Echo可以理解为“半成品”的Echo。某些命令的Echo计算比较耗时，为了避免用户操作过于卡顿，可以将Echo Mode切换至Partial Echo，随后echo流程会去调用tcmd中配置的“partial_echo_obj”函数。

当tcmd配置了属性“partial_echo_obj”或“echo_switch”后，命令面板上会显示Echo Mode切换按钮，可以进行 Full Echo → Partial Echo → No Echo 三种模式的轮流切换。

具体可参考命令 FtFillet2 的实现。

五、总结和展望

模板命令的开发流程还是比较繁琐的，要配置.tcmd文件，要配置各种.zcui资源文件，如果需要显示OptionForm的话还得创建.ui文件。

当我们在开发过程中遇到问题时，除了查阅文档之外，还可以多多向周围的同事们请教。

模板命令框架有不少历史包袱，比如.tcmd中参数的options字段非常丰富，甚至是”过于丰富“了。由于代码历史悠久，一些字段的含义没有清晰地流传下来，具体用途已经说不清了。目前依然还没有一篇文档能够对所有的options字段进行充分的整理。其实很多配置项都是为了满足某个（些）业务需求而加，一些本可以写在业务代码里面的逻辑，被塞在了tcmd中，意图被掩藏。而为了实现这些配置项，在通用流程塞满了各种的if判断，让代码可读性下降，导致多年之后，负责维护业务的人和负责维护通用流程的人都看不懂这些配置到底是干嘛的……

另外，由于框架比较老，模板命令的开发方式依然残留着不少C语言的模样，C++类封装不够充分，开发复杂业务功能会比较困难。（笔者个人见解）

但无论如何，ZW3D的模板命令框架是经得起历史考验的，这么多年来，它确实满足了绝大部分业务功能的开发。

附录 完整示例代码
/**
**   (C) Copyright 2024, ZWSOFT Co., LTD.(Guangzhou) All Rights Reserved.
*/
#include <random>

VmRegisterFile(Genshin);
VmRegisterTemplate(Genshin, Genshin, ZW_ANY_PRODUCT);
VmRegisterEchOFunction(Genshin, GenshinEO);
VmRegisterInitFunction(Genshin, GenshinInit);
VmRegisterInitafterFunction(Genshin, GenshinInitAft);
VmRegisterCbFunction(Genshin, GenshinPointCb);

#define V_FLD_PNT1 1
#define V_FLD_PNT2 2
#define V_FLD_LIMIT_STR 3
#define V_FLD_MIN_LENGTH 4
#define V_FLD_MAX_LENGTH 5
#define V_FLD_COLOR 7

static int Loc_GetInputPoint(int idx_in, VsPoint *start_pnt, VsPoint *end_pnt);
static void Loc_GenerateRandomNumber(double *pMinValue, double *pMaxValue);
static bool Loc_ValidateLineLength(const VsPoint &p1, const VsPoint &p2, const VsLim1 &limit);

/*******************************************************************/
/* PRIVATE */
static int Genshin
(
int idx_in,
int *idx_out
)
{
    VsPoint start_pnt = {};
    VsPoint end_pnt = {};
    if (Loc_GetInputPoint(idx_in, &start_pnt, &end_pnt))
        return 1;

    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min))
        return 1;
    if (VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
        return 1;

    if (!Loc_ValidateLineLength(start_pnt, end_pnt, limit))
    {
        zwAlert(zwlog_cad) << "The length of the line doesn't satisfy the answer.";
        return 1;
    }

    return 0;
}

/*******************************************************************/
/* PRIVATE */
static void GenshinEO
(
int idx_in,
VsObjHandle *oh_echo
)
{
    int iErr = 0;
    VsPoint start_pnt = {};
    VsPoint end_pnt = {};

    if (iErr = Loc_GetInputPoint(idx_in, &start_pnt, &end_pnt))
        return;

    VsObjHandle ohLine;
    VsLine zLn = {start_pnt, end_pnt};

    {
        C_AUTO_REVERT_BIN_INIT(PRJ_BIN);
        if (iErr = CdLine3Create(&zLn, &VgCdEchoAt, &ohLine))
            return;
        if (iErr = CdObjAddTo(&ohLine, oh_echo))
            return;
    }
}

/*******************************************************************/
/* PRIVATE */
static void GenshinInit
(
int idx_in
)
{
    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min) || VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
    {
        /* Doesn't get value from fld4 and fld5 successfully, so it means there are not data.*/
        Loc_GenerateRandomNumber(&limit.min, &limit.max);
        if (VxLogNum(idx_in, V_FLD_MIN_LENGTH, V_NUM, limit.min))
            return;
        if (VxLogNum(idx_in, V_FLD_MAX_LENGTH, V_NUM, limit.max))
            return;
    }
}

/*******************************************************************/
/* PRIVATE */
static int GenshinInitAft
(
int idx_in
)
{
    VsLim1 limit = {};
    if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min))
        return 1;
    if (VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
        return 1;

    std::stringstream ss;
    ss << limit.min << "mm ~ " << limit.max << "mm"; // assume the unit is "mm"
    if (VxLogStr(idx_in, V_FLD_LIMIT_STR, ss.str().c_str()))
        return 1;
    (void)InOptFormSetVal(V_FLD_LIMIT_STR, V_FALSE);
    return 0;
}

/*******************************************************************/
/* PRIVATE */
static int Loc_GetInputPoint
(
int idx_in,
VsPoint *start_pnt,
VsPoint *end_pnt
)
{
    if (!start_pnt || !end_pnt)
    {
        zwAssert(zwlog_cad, false);
        return 1;
    }
    /* Get start point */
    if (VxInpPnt(idx_in, V_FLD_PNT1, 3, reinterpret_cast<double *>(start_pnt)))
        return 1;
    /* Get end point */
    if (VxInpPnt(idx_in, V_FLD_PNT2, 3, reinterpret_cast<double *>(end_pnt)))
        return 1;
    return 0;
}

/*******************************************************************/
/* PRIVATE */
static void Loc_GenerateRandomNumber
(
double *pMinValue,
double *pMaxValue
)
{
    if (!pMaxValue || !pMinValue)
    {
        zwAssert(zwlog_cad, false);
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(50.0, 100.0);
    double minValue = dis(gen);
    double maxValue = dis(gen);
    if (VxDoubleGreaterThan(minValue, maxValue))
    {
        std::swap(minValue, maxValue);
    }

    *pMinValue = minValue;
    *pMaxValue = maxValue;
}

/*******************************************************************/
/* PRIVATE */
static bool Loc_ValidateLineLength
(
const VsPoint &p1,
const VsPoint &p2,
const VsLim1 &limit
)
{
    double input = std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2);
    double min = std::pow(limit.min, 2);
    double max = std::pow(limit.max, 2);
    if (VxDoubleGreaterThan(input, min) && VxDoubleLessThan(input, max))
    {
        return true;
    }
    return false;
}

/*******************************************************************/
/* PRIVATE */
static int GenshinPointCb
(
char *form, /* I: name of active form. */
int field,  /* I: id of active field. */
int idx_in  /* I: index of input data-object (class=VDATA) */
)
{
    if (field != V_FLD_PNT1 && field != V_FLD_PNT2)
    {
        zwAssert(zwlog_cad, false);
        return 1;
    }

    VsPoint start_pnt = {};
    VsPoint end_pnt = {};
    if (!Loc_GetInputPoint(idx_in, &start_pnt, &end_pnt))
    {
        VsLim1 limit = {};
        if (VxInpNum(idx_in, V_FLD_MIN_LENGTH, &limit.min))
            return 1;
        if (VxInpNum(idx_in, V_FLD_MAX_LENGTH, &limit.max))
            return 1;

        std::string formStr;
        if (InFormName(formStr))
            return 1;
        if (Loc_ValidateLineLength(start_pnt, end_pnt, limit))
        {
            uiColorRGBSet(formStr.c_str(), V_FLD_COLOR, 0, 255, 0);
        }
        else
        {
            uiColorRGBSet(formStr.c_str(), V_FLD_COLOR, 255, 0, 0);
        }
    }

    return 0;
}




<?xml version="1.0" encoding="UTF-8"?>
<templates xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="../schemas/Template.xsd">
    <template name="Genshin">
        <property name="function">Genshin</property>
        <property name="echo_obj">GenshinEO</property>
        <property name="init">GenshinInit</property>
        <property name="init_after">GenshinInitAft</property>
        <parameters>
            <parameter luid="1" description="1st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a start point of the line.</property>
                <property name="callback">GenshinPointCb</property>
            </parameter>
            <parameter luid="2" description="2st point" type="point">
                <property name="options">/face/edge/curve/point/,ddd_drag</property>
                <property name="prompt">Pick a end point of the line.</property>
                <property name="callback">GenshinPointCb</property>
            </parameter>
            <parameter trigger="true" luid="6" type="continue">
                <property name="prompt">&lt;middle-click&gt; to finish.</property>
            </parameter>
            <parameter luid="3" description="Limitation" type="string">
                <property name="prompt">The length limit of the line.</property>
            </parameter>
            <parameter luid="4" description="Minimum length" type="number">
            </parameter>
            <parameter luid="5" description="Maximum length" type="number">
            </parameter>
        </parameters>
        <!-- Field = 7 reserved for color -->
    </template>
</templates>




<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>Genshin</class>
 <widget class="ZsCc::Form" name="Genshin">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>275</width>
    <height>157</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>Form</string>
  </property>
  <property name="functionName">
   <string notr="true"/>
  </property>
  <property name="mode">
   <enum>ZsCc::Form::Dockable</enum>
  </property>
  <layout class="QVBoxLayout" name="verticalLayout">
   <property name="leftMargin">
    <number>2</number>
   </property>
   <property name="topMargin">
    <number>2</number>
   </property>
   <property name="rightMargin">
    <number>2</number>
   </property>
   <property name="bottomMargin">
    <number>2</number>
   </property>
   <item>
    <widget class="ZsCc::DrawbackBoxGroup" name="DrawbackBoxGroup">
     <property name="currentIndex">
      <number>0</number>
     </property>
     <widget class="QWidget" name="page_0">
      <property name="windowTitle">
       <string>Required</string>
      </property>
      <layout class="QGridLayout" name="gridLayout_0" columnstretch="1,0">
       <item row="3" column="0">
        <widget class="QLabel" name="id7label">
         <property name="text">
          <string>Traffic light</string>
         </property>
        </widget>
       </item>
       <item row="3" column="1">
        <widget class="ZsCc::ColorPicker" name="id7">
         <property name="type" stdset="0">
          <number>0</number>
         </property>
         <property name="id" stdset="0">
          <number>7</number>
         </property>
        </widget>
       </item>
       <item row="2" column="0">
        <widget class="QLabel" name="id3label">
         <property name="text">
          <string>Limitation</string>
         </property>
        </widget>
       </item>
       <item row="0" column="0">
        <widget class="QLabel" name="id1label">
         <property name="text">
          <string>1st point</string>
         </property>
        </widget>
       </item>
       <item row="1" column="0">
        <widget class="QLabel" name="id2label">
         <property name="text">
          <string>2st point</string>
         </property>
        </widget>
       </item>
       <item row="1" column="1">
        <widget class="ZsCc::Point" name="id2">
         <property name="id" stdset="0">
          <number>2</number>
         </property>
        </widget>
       </item>
       <item row="2" column="1">
        <widget class="ZsCc::String" name="id3">
         <property name="id" stdset="0">
          <number>3</number>
         </property>
        </widget>
       </item>
       <item row="0" column="1">
        <widget class="ZsCc::Point" name="id1">
         <property name="id" stdset="0">
          <number>1</number>
         </property>
        </widget>
       </item>
      </layout>
     </widget>
    </widget>
   </item>
  </layout>
 </widget>
 <customwidgets>
  <customwidget>
   <class>ZsCc::Point</class>
   <extends>QWidget</extends>
   <header>nui/CommonControls/Template/CcPoint.hpp</header>
   <container>1</container>
  </customwidget>
  <customwidget>
   <class>ZsCc::String</class>
   <extends>QWidget</extends>
   <header>nui/CommonControls/Template/CcString.hpp</header>
   <container>1</container>
  </customwidget>
  <customwidget>
   <class>ZsCc::ColorPicker</class>
   <extends>QToolButton</extends>
   <header>nui/CommonControls/CcColorPicker.hpp</header>
  </customwidget>
  <customwidget>
   <class>ZsCc::DrawbackBoxGroup</class>
   <extends>QWidget</extends>
   <header>nui/CommonControls/CcDrawbackBoxGroup.hpp</header>
   <addpagemethod>addPage</addpagemethod>
   <container>1</container>
  </customwidget>
  <customwidget>
   <class>ZsCc::Form</class>
   <extends>QDialog</extends>
   <header>nui/CommonControls/CcForm.hpp</header>
   <container>1</container>
  </customwidget>
 </customwidgets>
 <resources/>
 <connections/>
</ui>





