{ stdenv, cmake, civetweb }:

let
  civetweb_embed = civetweb.overrideAttrs (oldAttrs: {
    pname = "civetweb_embed";
    cmakeFlags = [
      "-DBUILD_SHARED_LIBS=OFF"
      "-DCIVETWEB_ENABLE_CXX=OFF"
      "-DCIVETWEB_ENABLE_IPV6=OFF"
      "-DCIVETWEB_ENABLE_SERVER_EXECUTABLE=OFF"
      "-DCIVETWEB_ENABLE_SSL=OFF"
      # The civetweb unit tests rely on downloading their fork of libcheck.
      "-DCIVETWEB_BUILD_TESTING=OFF"
    ];
    patches = [ ./cwpatch/mingw-cross.patch ];
  });
in
stdenv.mkDerivation rec {
  pname = "realworld-c-civetweb";
  version = "0.1.0";

  src = ./src;

  nativeBuildInputs = [ cmake ];
  buildInputs = [ civetweb_embed ];

  cmakeFlags = [
    # FIXME: This is a hack to get the civetweb_embed library to be found.
   "-Dcivetweb_LIBRARY_DIR=${civetweb_embed}/lib"
  ];

}
