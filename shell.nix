{ lib ? import <nixpkgs/lib>
, pkgs ? import <nixpkgs> { }
, mkShell ? pkgs.mkShell
, zipfs-rw ? pkgs.callPackage ./. { fuse = if pkgs.stdenv.isDarwin then osxfuse else fuse3; }
, bashInteractive ? pkgs.bashInteractive
, clang-tools ? pkgs.clang-tools
, fuse3 ? pkgs.fuse3
, gitAndTools
, muonStandalone ? pkgs.muonStandalone or null
, osxfuse ? pkgs.osxfuse
, samurai ? pkgs.samurai
, shellcheck ? pkgs.shellcheck
, unzip ? pkgs.unzip
, zip ? pkgs.zip
}:

mkShell {
  packages = [
    bashInteractive
    clang-tools
    gitAndTools.gitFull
    samurai
    shellcheck
    unzip
    zip
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
