{ stdenv, cmake, nur }:

stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = with nur.repos.jacekszymanski;
    [ civetweb-dev sqlite-dev l8w8jwt-dev ];

}
