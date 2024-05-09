{
  description = "flake for building realworld c example";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
    nur-dev = {
      url = "github:jacekszymanski/nur-dev";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs = { self, nixpkgs, flake-utils, nur-dev }:
    (flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
        config.packageOverrides = _: { inherit jsz-dev; };
      };
      jsz-dev = import nur-dev { inherit pkgs; };
      realworld = import ./. { inherit pkgs; };
    in {
      inherit pkgs;
      packages = {
        inherit realworld;
      };
      defaultPackage = realworld;
    }));
}
