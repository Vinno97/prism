<h1>Prism</h1>

<h2>Installation guide</h2>
<h3>Unix</h3>
<h4>Basic installation</h4>
<p>

Clone the repository
```terminal
$ sudo apt-get cmake
$ sudo apt install libsdl2-dev libsdl2-image-dev libassimp-dev libglew-dev 
$ cd "projectfolder" 
$ cmake .
$ cmake --build .
$ cd out
$ ./Prism.Game
```
</p>
<h4>Fixes for known errors</h4>
<p>
<strong>[dependency name] is not installed.</strong>
<br>Follow terminal instructions. Probably just a sudo apt-get.
<br>
<br><strong>Could not open OpenGL - glxbadfbconfig</strong>
<br>Go to Software & Updates.
<br>Go to Additional Drivers tab.
<br>Press 'Using Nvidia driver Metapackage'.
<br>Reboot.

<br>Still doesn't work?
<br>Disable Secure Boot in BIOS.
</p>
