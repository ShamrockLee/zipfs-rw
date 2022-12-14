{ lib
, stdenv
, callPackage
, meson
, ninja
, pkg-config
, fuse
, fuse3
, libtree-c ? callPackage ./libtree-c.nix { }
, libzip
, osxfuse
, shellcheck
, self ? callPackage ./. { fuse = if stdenv.hostPlatform.isDarwin then osxfuse else fuse3; }
}:

stdenv.mkDerivation {
  pname = "zipfs-rw";
  version = "0.1.0";

  src = lib.cleanSource ./.;

  passthru.tests =
    lib.optionalAttrs stdenv.hostPlatform.isLinux
      {
        zipfs-rw-fuse2 = self.override {
          inherit fuse;
          self = self.passthru.tests.zipfs-rw-fuse2;
        };
        zipfs-rw-fuse3 = self.override {
          fuse = fuse3;
          self = self.passthru.tests.zipfs-rw-fuse3;
        };
        zipfs-rw-nix-builtin-libtree-c = self.override {
          libtree-c = callPackage ./libtree-c.nix { };
        };
        zipfs-rw-meson-builtin-libtree-c = self.override {
          libtree-c = null;
        };
      }
    // lib.optionalAttrs stdenv.hostPlatform.isDarwin
      {
        zipfs-rw-osxfuse = self.override {
          fuse = osxfuse;
          self = self.passthru.tests.zipfs-rw-osxfuse;
        };
      }
  ;

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
  ];

  buildInputs = [
    fuse
    libtree-c
    libzip
  ]
  ;

  doCheck = true;

  checkInputs = [
    shellcheck
  ];
}
