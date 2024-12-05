**Scene Editor v12112976**
-
Developed by Kate Nicole Young

How to run:
Compile and run on VS Community 2022.

Entry Class: main.cpp `main()` function.

Game Engine Parsers: https://drive.google.com/drive/u/0/folders/1GfhIFXwTf-d_vOkBLWbJ9wqW1D0qfIcW

*How to Load Scenes:*
-
*Scene Editor*
1. Go to File > Open. It will open "Default.level". Please rename your Level Asset File as such to make it work.

*Unity Parser*
1. Import UnityLevel.cs and UnityLevelEditor.cs anywhere in the Assets folder. 
2. Drag and drop your Level Asset (.level) file anywhere in the Assets folder. 
3. In any scene, create a new Game Object and attach the UnityLevel.cs as a component. 
4. Drag your Level Asset (.level) file into the Asset field in the component.
5. Click Load Scene. Your Scene should be loaded and parented under the Game Object containing your Unity Level Component.

*Unreal Engine Parser*
1. Paste all the files into their respective folders into any Unreal Project as organized in the Unreal folder. (Note: "GDENG03Final" is the Project Name).
2. Rename the GDENG03Final instances in the scripts (.cpp and .h) with your own Project Name.
3. Right-click on LevelManager (Editor Utility Widget) and click Run Editor Utility Widget.
4. Add your Level Asset file into the root project directory beside the .uproject file. 
5. Input your Level Asset file name into the field beside the Load Level button. (i.e. Default.level).
6. Click the Load Level button. Please note: do not load two times in the same level. Sorry for the inconvenience.

*Where to find the Level Asset files in Scene Editor:*
-
Navigate to the root project directory. Open the Levels folder and the saved level should be there named "Default.level". You can grab this to use in the other engines.

*How to Save Scenes:*
-
*Scene Editor*
1. Go to File > Save. It will save your scene into "Default.level".

*Unity Parser*
1. In the Unity Level Component (refer to How to Load Scenes to see how to set this up), click Save Scene. This will save all the children of the owner into a Level Asset File.
2. The Level Asset file should appear in the Assets folder after a short while.

*Unreal Engine Parser*
1. In the Level Manager widget, input the filename you want to save the scene as into the field beside the Save Level Button. Then press Enter.
2. Click the Save Level Button. Any Actor with tag "Game Object" will be saved into your Level Asset file.
3. Your Level Asset file will be generated and ready beside the Level Asset file you imported (beside the Unreal Project file).

*How to Edit Scenes:*
-
1. If you want to edit the existing objects, feel free to do so and save as normal.
2. If you want to add new objects, please do the following:
 - Unity: Change the tag of the Object to its Primitive Type (should be generated already). Make sure the object is parented under the Unity Level Object.
 - Unreal: Add tags in the following order: "Game Object", Primitive Type (Cube, Capsule, Sphere, Cylinder, Plane), Physics Rigidbody Type (Dynamic, Kinematic, Static).
3. Deleting objects counts as editing so refer to #1.
