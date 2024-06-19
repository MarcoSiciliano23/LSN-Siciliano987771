{ pkgs }: {
	deps = [
   pkgs.root
   pkgs.run
   pkgs.python39Packages.clvm-tools
   pkgs.twelf
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}