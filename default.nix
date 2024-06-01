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

}
