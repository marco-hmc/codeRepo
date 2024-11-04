
Creating a window

### OpenGL 是什么？

OpenGL（Open Graphics Library）是一个跨平台的、用于渲染2D和3D图形的应用程序编程接口（API）。它由Khronos Group维护和管理，广泛应用于游戏开发、CAD、虚拟现实和科学可视化等领域。

#### 主要特点：
- **跨平台**：OpenGL 支持多种操作系统，包括 Windows、macOS 和 Linux。
- **硬件加速**：利用 GPU 的硬件加速能力，提高图形渲染性能。
- **广泛支持**：被许多图形应用程序和游戏引擎广泛采用。
- **开放标准**：由 Khronos Group 维护，任何人都可以使用和实现。

#### 使用场景：
- **游戏开发**：用于创建高性能的2D和3D游戏。
- **科学可视化**：用于渲染复杂的科学数据和模拟。
- **虚拟现实**：用于创建沉浸式的虚拟现实体验。
- **CAD**：用于计算机辅助设计和建模。

### OpenGL 和 GLFW 的关系是什么？

GLFW 是一个专门为 OpenGL 设计的库，它提供了创建窗口、上下文和处理输入的基本功能。GLFW 使得开发人员可以更容易地使用 OpenGL 进行图形渲染，而不需要处理底层的窗口系统和输入事件。

#### 主要特点：
- **创建 OpenGL 上下文**：GLFW 提供了创建和管理 OpenGL 上下文的功能。
- **窗口管理**：GLFW 允许开发人员创建和管理窗口，并设置窗口参数。
- **输入处理**：GLFW 提供了处理键盘、鼠标和其他输入设备的功能。
- **跨平台支持**：GLFW 支持 Windows、macOS 和 Linux，使得开发人员可以编写跨平台的图形应用程序。

#### 使用场景：
- **OpenGL 应用程序开发**：GLFW 是开发 OpenGL 应用程序的理想选择，提供了创建窗口和处理输入的基本功能。
- **游戏开发**：GLFW 常用于游戏开发，特别是需要跨平台支持的游戏。
- **图形学习和实验**：GLFW 是学习和实验 OpenGL 的理想工具。

### 总结

- **OpenGL** 是一个跨平台的图形渲染 API，用于创建2D和3D图形。
- **GLFW** 是一个专门为 OpenGL 设计的库，提供了创建窗口、上下文和处理输入的基本功能，使得开发人员可以更容易地使用 OpenGL 进行图形渲染。


Building GLFW

* The resulting library from compilation.
* The include folder.

Since CMake generated a project file that already contains the proper configuration settings we only have to build the solution. CMake should've automatically configured the solution so it compiles to a 64-bit library; now hit build solution. This will give us a compiled library file that can be found in build/src/Debug named glfw3.lib.

Once we generated the library we need to make sure the IDE knows where to find the library and the include files for our OpenGL program. There are two common approaches in doing this:

We find the /lib and /include folders of the IDE/compiler and add the content of GLFW's include folder to the IDE's /include folder and similarly add glfw3.lib to the IDE's /lib folder. This works, but it's is not the recommended approach. It's hard to keep track of your library and include files and a new installation of your IDE/compiler results in you having to do this process all over again.
Another approach (and recommended) is to create a new set of directories at a location of your choice that contains all the header files/libraries from third party libraries to which you can refer to from your IDE/compiler. You could, for instance, create a single folder that contains a Libs and Include folder where we store all our library and header files respectively for OpenGL projects. Now all the third party libraries are organized within a single location (that can be shared across multiple computers). The requirement is, however, that each time we create a new project we have to tell the IDE where to find those directories.
Once the required files are stored at a location of your choice, we can start creating our first OpenGL GLFW project.
Our first project
First, let's open up Visual Studio and create a new project. Choose C++ if multiple options are given and take the Empty Project (don't forget to give your project a suitable name). Since we're going to be doing everything in 64-bit and the project defaults to 32-bit, we'll need to change the dropdown at the top next to Debug from x86 to x64:

Image of how to switch from x86 to x64
Once that's done, we now have a workspace to create our very first OpenGL application!

Linking
In order for the project to use GLFW we need to link the library with our project. This can be done by specifying we want to use glfw3.lib in the linker settings, but our project does not yet know where to find glfw3.lib since we store our third party libraries in a different directory. We thus need to add this directory to the project first.

We can tell the IDE to take this directory into account when it needs to look for library and include files. Right-click the project name in the solution explorer and then go to VC++ Directories as seen in the image below:

Image of Visual Studio's VC++ Directories configuration
From there on out you can add your own directories to let the project know where to search. This can be done by manually inserting it into the text or clicking the appropriate location string and selecting the <Edit..> option. Do this for both the Library Directories and Include Directories:

Image of Visual Studio's Include Directories configuration
Here you can add as many extra directories as you'd like and from that point on the IDE will also search those directorie when searching for library and header files. As soon as your Include folder from GLFW is included, you will be able to find all the header files for GLFW by including <GLFW/..>. The same applies for the library directories.

Since VS can now find all the required files we can finally link GLFW to the project by going to the Linker tab and Input:

Image of Visual Studio's link configuration
To then link to a library you'd have to specify the name of the library to the linker. Since the library name is glfw3.lib, we add that to the Additional Dependencies field (either manually or using the <Edit..> option) and from that point on GLFW will be linked when we compile. In addition to GLFW we should also add a link entry to the OpenGL library, but this may differ per operating system:

OpenGL library on Windows
If you're on Windows the OpenGL library opengl32.lib comes with the Microsoft SDK, which is installed by default when you install Visual Studio. Since this chapter uses the VS compiler and is on windows we add opengl32.lib to the linker settings. Note that the 64-bit equivalent of the OpenGL library is called opengl32.lib, just like the 32-bit equivalent, which is a bit of an unfortunate name.

OpenGL library on Linux
On Linux systems you need to link to the libGL.so library by adding -lGL to your linker settings. If you can't find the library you probably need to install any of the Mesa, NVidia or AMD dev packages.

Then, once you've added both the GLFW and OpenGL library to the linker settings you can include the header files for GLFW as follows:


#include <GLFW/glfw3.h>
For Linux users compiling with GCC, the following command line options may help you compile the project: -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl. Not correctly linking the corresponding libraries will generate many undefined reference errors.
This concludes the setup and configuration of GLFW.

GLAD
We're still not quite there yet, since there is one other thing we still need to do. Because OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a driver that the specific graphics card supports. Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time. It is then the task of the developer to retrieve the location of the functions he/she needs and store them in function pointers for later use. Retrieving those locations is OS-specific. In Windows it looks something like this:


// define the function's prototype
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// find the function and assign it to a function pointer
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// function can now be called as normal
unsigned int buffer;
glGenBuffers(1, &buffer);
As you can see the code looks complex and it's a cumbersome process to do this for each function you may need that is not yet declared. Thankfully, there are libraries for this purpose as well where GLAD is a popular and up-to-date library.

Setting up GLAD
GLAD is an open source library that manages all that cumbersome work we talked about. GLAD has a slightly different configuration setup than most common open source libraries. GLAD uses a web service where we can tell GLAD for which version of OpenGL we'd like to define and load all relevant OpenGL functions according to that version.

Go to the GLAD web service, make sure the language is set to C++, and in the API section select an OpenGL version of at least 3.3 (which is what we'll be using; higher versions are fine as well). Also make sure the profile is set to Core and that the Generate a loader option is ticked. Ignore the extensions (for now) and click Generate to produce the resulting library files.

Make sure you use the GLAD1 version from: https://glad.dav1d.de/ as linked above. There's also a GLAD2 version that won't compile here.
GLAD by now should have provided you a zip file containing two include folders, and a single glad.c file. Copy both include folders (glad and KHR) into your include(s) directoy (or add an extra item pointing to these folders), and add the glad.c file to your project.

After the previous steps, you should be able to add the following include directive above your file:


#include <glad/glad.h> 
Hitting the compile button shouldn't give you any errors, at which point we're set to go for the next chapter where we'll discuss how we can actually use GLFW and GLAD to configure an OpenGL context and spawn a window. Be sure to check that all your include and library directories are correct and that the library names in the linker settings match the corresponding libraries.

Additional resources
GLFW: Window Guide: official GLFW guide on setting up and configuring a GLFW window.
Building applications: provides great info about the compilation/linking process of your application and a large list of possible errors (plus solutions) that may come up.
GLFW with Code::Blocks: building GLFW in Code::Blocks IDE.
Running CMake: short overview of how to run CMake on both Windows and Linux.
Writing a build system under Linux: an autotools tutorial by Wouter Verholst on how to write a build system in Linux.
Polytonic/Glitter: a simple boilerplate project that comes pre-configured with all relevant libraries; great for if you want a sample project without the hassle of having to compile all the libraries yourself.
