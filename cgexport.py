import os, shutil, argparse

# user configuration
default_szip_path	= R'C:\Program Files\7-Zip\7z.exe'
default_src_dir		= R"."

# exclude patterns of files and directories
exclude_pattern = [
	"$~*", "~$*", "*.bak", "*cache*", "*.tmp", "temp", "tmp",		# temp
	"*.vcxproj.user", "*.exp", "*.pdb", ".vs", "Debug", "Release",	# vcpp files
	".vs", ".vscode", "Debug", "Release",	# vcpp directories
	"dragon.*.bin", "dragon.*.txt",			# temporary mesh (e.g., dragon in transform)
	".obj",									# gcc intermediate dir
	"*.7z", "*.zip",						# archives
	".*", ".git*",							# hidden dirs/files
	"*.bat", "*.py", "*sync"				# misc scripts
]

# find and build 7-zip path
szip = default_szip_path
if not os.path.exists(szip): szip = shutil.which("7z.exe")	# try once again with ones in the system path
if not szip or not os.path.exists(szip): print( "error: 7z.exe not exists" ); exit()
if szip!=default_szip_path: print( "7z.exe is found at: " + szip )	
if szip.find(" "): szip = '"'+szip+'"' # enclose with auto-quotation

# parse arguments
parser = argparse.ArgumentParser(description='build *.7z for cg course submission')
parser.add_argument('--src',default=default_src_dir,help='source directory (default: \".\")')	# (optional) source dir
parser.add_argument('dst',help='7z file name') # 7z file path
args = parser.parse_args()

# set src and dst
src	= args.src
dst = args.dst

# correct dst extension to 7z
fname, fext = os.path.splitext(dst)
if fext!=".7z": dst = fname+".7z"

# 7-zip switch and option
sw	= "u"
opt	= "-stl -bb3 -up0q0 -r -ssw -md48m -mx9 -mmt8"
xr	= "-xr!"+" -xr!".join(exclude_pattern)

# build cmd
cmd = " ".join([szip,sw,dst,src,opt,xr])
print("\n"+cmd)
os.system(cmd)
