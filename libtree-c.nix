{ lib
, stdenv
}:
stdenv.mkDerivation {
  pname = "libtree-unstable";
  version = "0.0.0";

  src = lib.cleanSource ./libtree;

  preInstall = ''
    installFlagsArray+=( "prefix=$prefix" )
  '';

  meta = with lib; {
    description = "A mixin-style C library implementing famous binary search trees";
    homepage = "https://github.com/fbuihuu/libtree";
    license = licenses.lgpl21Only;
    platforms = platforms.all;
  };
}
