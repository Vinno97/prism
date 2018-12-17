with import <nixpkgs> {};

let
#    clangStdenv7 = overrideCC clangStdenv clang_7;
    stdenv8 = overrideCC stdenv gcc8;
in
#    clangStdenv7.mkDerivation rec {
    stdenv8.mkDerivation rec {
        name = "env";
        env = buildEnv {
            name = name;
            paths = buildInputs;
        };
        buildInputs = [
            cmake
            freetype
            fmt
            pkgconfig
            SDL2
            SDL2_image
            SDL2_mixer
            assimp
            glm
            glew
            glxinfo
            which
        ];
        OpenGL_GL_PREFERENCE = "GLVND";
        SDL_MODULE_PATH = "/nix/store/sxxy01wn82n7wjl5a384344m2i4xszx6-cmake-3.12.1/share/cmake-3.12/Modules";

    }
