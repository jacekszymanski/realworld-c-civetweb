{ pkgs ? (builtins.getFlake (toString ./.)).pkgs.${builtins.currentSystem}
}:

let
  inherit (pkgs) stdenv cmake jsz-dev;
in
stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = with jsz-dev; [
    civetweb-dev
    sqlite-dev
    l8w8jwt-dev
    cjson-dev
    cmocka-dev
  ];

  preConfigure = ''
    CFLAGS+=" -g -O0 -Wall -Wextra -Werror "
    CFLAGS+=" -Wno-unused-parameter -Wno-unused-variable "
    CFLAGS+=" -DLOGLEVEL=5 "
    CFLAGS+=" -ffile-prefix-map=$(echo $NIX_BUILD_TOP|sed -e s,/private,,g)/= "

    export CFLAGS
  '';

}
