# Source Engine 2007 - CLion/CMake
###### Experimental MSVC v143, C++ 17 branch

This is the 2007 Source Engine leak transferred to a raw CMake project, made in CLion. It should be noted
that this project doesn't need CLion to work, it is just a collection of carefully configured CMake projects and should
be able to build with just CMake and The ~~v80~~ v143 MSVC toolkit. This project is still entirely in development, and any user
end should expect changes. I will try my best to utilize branches as to not break anything.

### **Warning**
This is a highly experimental branch and may not function as expected. The following setup guide may be outdated ant
not work for this branch, as these branches often require special handling. This warning will be removed when the setup
guide is updated and this branch is no longer experimental.

## Setup Guide [CLion]

This setup guide should get you from an empty IDE to running and building Portal and all the supported engine modules,
including some necessary file patching to get resources working and some non-buildable binaries put in place.

1. Install [CLion](https://www.jetbrains.com/clion/). CLion is a paid application developed by [JetBrains](https://www.jetbrains.com/),
however you can get their entire toolkit for $20/month, which is very worth it. Otherwise, you can live off CLions free trials
that they renew with every update, so if you're just a hobbyist you can scrape by that way.


2. Download and install Visual Studio 2022 with the Desktop C++ Development workload. You need this so you have access to
the MSVC v143 compiler, if you know how else you can get this then do whatever works.


3. Pull this repository in CLion. If you're not at the `Welcome` screen, it's `File > New > Project from Version Control..`,
otherwise, just click `Get from VCS` and follow the screen prompt.
   ![](https://media.discordapp.net/attachments/365987434800087041/976782626364997652/clion64_wFynBgIn68.gif?width=827&height=676)


4. Configure the build types appropriately. This project supports release and debug at the time of writing. Just click
the `+` in the top left of the Project Wizard, it will automatically create a second build type `Release`. Then for both
build types `Debug` and `Release`, set their Toolchain to ~~`Visual Studio 2005`~~ `Visual Studio 2022` that you setup in the 2nd step.
![](https://media.discordapp.net/attachments/365987434800087041/976783039256477706/clion64_9fkWmVhfYm.gif?width=816&height=676)


5. After the project finishes setting up, you'll want to build all the modules. `Build > Build All in ...` This is going to 
take a considerable amount of time, maybe 15 minutes or so. Parallel build configurations are on my todo list, but for a 
first time setup, it's not terrible. CMake does a good job of caching, making future builds *considerably* faster.<br>
*note*: This isn't strictly necessary, but this will happen now or later, directly or indirectly, so may as well do it now.
![](https://cdn.discordapp.com/attachments/365987434800087041/976787183883132938/unknown.png)


6. Create a `launch_portal` configuration. This is optional but highly recommended, it allows you to click one button that
will compile the Portal client and server, and then run the game from within CLion. The pattern for this is applicable for
any of the games here, but Portal is the only one supported at the time of writing.<br><br>![](https://media.discordapp.net/attachments/365987434800087041/976796005515280424/unknown.png)
<br>Go to the top right next to the build button (looks like a hammer), click the dropdown, and click `Edit Configurations`. From there, click the `+` in the
top left, and add a `CMake Application`.<br><br>You can name it whatever you want, I named mine `launch_portal`. Set the
target to `launcher_main`, and the executable should automatically be set to `launcher_main` as well. Then, you'll want
to add `-game portal -allowdebug` to the program arguments. This will start portal, and `-allowdebug` tells Source Engine
that it's allowed to load engine modules that were compiled with debug information, without this flag, those modules will
crash the engine.<br><br>Lastly, at the bottom, below `Before launch`, add two Cmake Targets with the `+` in the top left;
one for `cl_portal` and one for `sv_portal`. This tells the configuration to build these two projects first. If you're doing
more stuff than just modifying the client and the server for portal, you might want to set this to just build `all targets`
instead.
![](https://media.discordapp.net/attachments/365987434800087041/976796373322186772/unknown.png?width=898&height=676)


7. The last thing we need to do is a bit of file "patching", where we take some game resources from other places and put
them into our game directory.<br><br>Firstly, we need to add some binaries. This project is incomplete and doesn't build
everything necessary to actually run the game independently, and there are also some binaries that can't be build. For
now, I have provided a [downloadable zip file](https://cdn.discordapp.com/attachments/365987434800087041/976801819328151612/leak_binaries_patch.zip)
that contains the binaries necessary. Take this and unzip it into your `run/bin/` directory in your project. You should
already have a few binaries in there if you did the "build all" step previously, otherwise the game won't run without those, too.
This configuration of binaries was tested very loosely, but I was able to load chamber 08 with default DirectX version.<br><br>
Next, you're going to want to gather some assets for the game. This should be the last bit of your file patch work. Firstly,
we are going to gather a collection of files from a known good download of `Source Unpack 3420`, which you can download [here](https://sourceunpack.gameabusefastcomplete.com/Portal_3420.7z).
Unzip that archive into a folder, open the `portal/` directory, and copy these folders: `cfg, maps, materials, models, reslists, 
resource, scenes, scripts, sound`. You'll want to copy these into the `run/portal/` folder in your project.
Next, just copy the entire `hl2` folder into your `run/` directory.<br><br>
Lastly, we are going to patch particle files. For this, you'll need a known good download of `Source Unpack 5135` which
you can download [here](https://sourceunpack.gameabusefastcomplete.com/Source_Unpack.zip). Next, unzip this archive just
like the previous one. Now, copy from the archive, the `portal/particles/` folder into `run/portal/`. Lastly, copy
`hl2/particles/` into `run/hl2/`. The reason for getting these from 5135 is that the leak version uses the newer particle
system.


8. That's it! You should now be able to run the previously created `launch_portal` configuration, and it should work.

## Project Structure

I wanted to briefly go over the layout of the project as it differs from the Visual Studio 2005 leak layout.


Firstly, I separated games from the engine. There is a `games/modules/` folder that contains all the games, and a
`engine/modules/` that contains all the engine modules. Outside of that, there is also a `/lib` folder where engine
modules will output their `.lib` files into `lib/public/`, otherwise, all other necessary libraries are stored there.

`/engine` contains `/common` and `/public` which contains all of the public headers and shared source files for engine
modules. It's not really cleaned up at all, I just moved it so it wasn't in the same area as the actual engine modules
source code and CMake projects.

I modified the structure of game source code. In the leak, games are structured in a `games/client/{game}` way where the
client, server, and shared code are all separated. I restructured it so that game folders contain `client`, `server`, and
`shared` instead.

Lastly, I made engine `.dll` files export to `/run/bin`, and tried to set it up so `/run` was a good run directory. So far,
it seems pretty well-structured all things considered, but I am open for criticisms and better ideas.

[//]: # (TODO: replace previous Discord links with links to files within the repo.)
