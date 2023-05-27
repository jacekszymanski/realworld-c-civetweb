{ stdenv, cmake, nur }:

let civetweb-dev = nur.repos.jacekszymanski.civetweb-dev;
in
stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ civetweb-dev ];

  cmakeFlags = [
    # FIXME: This is a hack to get the civetweb_embed library to be found.
   "-Dcivetweb_LIBRARY_DIR=${civetweb-dev}/lib"
  ];

}
