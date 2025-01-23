## cmakepresets.json

- configurePresets
  cmake 阶段，专业说法是 configure 阶段，即选择用什么构建工具，生成什么构建文件的过程。

  ```json
  "configurePresets": [
    {
      "name": "ninja",
      "hidden": true,
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build/ninja",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "make",
      "hidden": true,
      "generator": "Unix Makefiles",
      "binaryDir": "${sourceDir}/build/make",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    },
    {
      "name": "msbuild",
      "hidden": true,
      "generator": "Visual Studio 16 2019",
      "binaryDir": "${sourceDir}/build/msbuild",
      "architecture": {
        "value": "x64"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
    ]
  ```

- buildPresets
  make 阶段，专业说法是 build 阶段，即调用构建工具生成对象。

  ```json
  "buildPresets": [
    {
      "name": "ninja",
      "configurePreset": "ninja",
      "description": "Build with Ninja",
      "hidden": false,
      "jobs": 4
    },
    {
      "name": "make",
      "configurePreset": "make",
      "description": "Build with Make",
      "hidden": false,
      "jobs": 4
    },
    {
      "name": "msbuild",
      "configurePreset": "msbuild",
      "description": "Build with MSBuild",
      "hidden": false
    }
  ]
  ```
