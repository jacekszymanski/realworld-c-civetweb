{ stdenv, cmake, nur }:

let civetweb-dev = nur.repos.jacekszymanski.civetweb-dev;
    sqlite-dev = nur.repos.jacekszymanski.sqlite-dev;
in
stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ civetweb-dev sqlite-dev ];

  preConfigure = ''
    export LDFLAGS="-L${civetweb-dev}/lib -lcivetweb -L${sqlite-dev}/lib -lsqlite3"
    echo set LDFLAGS to $LDFLAGS
  '';

}
