# DI Game engine

## Structure
This is repo consist from next folders(not the actual layout in future)
* DI (contain actual code for engine)
* DISandbox (contain app which interact and use engine utilities)

## Features(kind of)
For now support only Linux systems
For now engine contain and consits from:
   * Window system (1 window only) + ImGUI
   * Entry  point  
   * Event system  (Uppon SDL events)
   * Loging system (App logs and DI logs) + opengl debug
   * Core Timer
   * Simple material system(Attribute handler, Support uniforms)
   * Camera support(without rolling)
   * Mem managment(not realy good)
   * Model loading(prebuild, support elements, vertecies, normals, colors,textures(diffuse,specular))

## Media
Usage example https://youtu.be/9xj_AYvZdhU

Screenshots:
* ![image](https://user-images.githubusercontent.com/70476470/166501050-6200d706-3dd9-4c05-970e-2165656b0c9e.png)
* ![image](https://user-images.githubusercontent.com/70476470/166501135-0f58c9f4-ff0c-4f79-b658-34925d1ba908.png)
* ![2022-05-03_19-52](https://user-images.githubusercontent.com/70476470/166501526-574ea1ec-0990-46cf-8ae9-37dc139db194.png)

## Build
### Dependencies
1. glu
2. glut

### Actual buildings
1. Download this repo
2. ``` git submodule update --init ```
3. ``` cmake -S . -B build ```
4. ``` cd build ```
5. ``` make -j4 ```

Now executabel appears in to DISandbox/build forlder. Go to there and run 
``` ./sandbox ```
