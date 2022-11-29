{ lib ? import <nixpkgs/lib>
, pkgs ? import <nixpkgs> { }
, mkShell ? pkgs.mkShell
, zipfs-rw ? pkgs.callPackage ./. { fuse = if pkgs.stdenv.isDarwin then osxfuse else fuse3; }
, bashInteractive ? pkgs.bashInteractive
, fuse3 ? pkgs.fuse3
, gitAndTools
, muonStandalone ? pkgs.muonStandalone or null
, osxfuse ? pkgs.osxfuse
, samurai ? pkgs.samurai
}:

mkShell {
  packages = [
    bashInteractive
    gitAndTools.gitFull
    samurai
  ]
  ++ lib.optional (! isNull muonStandalone && ! muonStandalone.meta.broken) muonStandalone
  ;

  inputsFrom = [
    zipfs-rw
  ];

  shellHook = ''
    SHELL="${bashInteractive}/bin/bash"; export SHELL
  '';
}
