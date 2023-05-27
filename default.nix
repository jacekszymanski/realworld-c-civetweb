{ stdenv, cmake, nur }:

let civetweb-dev = nur.repos.jacekszymanski.civetweb-dev;
in
stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ civetweb-dev ];

  preConfigure = ''
    export LDFLAGS="-L${civetweb-dev}/lib -lcivetweb"
    echo set LDFLAGS to $LDFLAGS
  '';

}
