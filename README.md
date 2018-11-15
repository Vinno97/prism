<h1>Prism</h1>

<h2>Installation guide</h2>
<h3>Unix</h3>
<h4>Basic installation</h4>
<p>
1. Clone the repository
2. $ sudo apt-get cmake
3. $ sudo apt install libsdl2-dev libsdl2-image-dev libassimp-dev libglew-dev 
4. $ cd \<projectfolder\> 
5. $ cmake .
6. $ cmake --build .
7. $ cd out
8. $ ./Prism.Game
</p>
<h4>Fixes for known errors</h4>
<p>
<strong>[dependency name] is not installed.</strong>
Follow terminal instructions. Probably just a sudo apt-get.

<strong>Could not open OpenGL - glxbadfbconfig</strong>
Go to Software & Updates.
Go to Additional Drivers tab.
Press 'Using Nvidia driver Metapackage'.
Reboot.

Still doesn't work?
Disable Secure Boot in BIOS.
</p>
