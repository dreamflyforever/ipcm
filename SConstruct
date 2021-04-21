env = Environment(CPPPATH = ['baselib', 'client', 'server'])

#env.Library('uplib',src, CFLAGS = ['-g', '-lpthread'])
env.SharedLibrary('mongoose', ['baselib/mongoose.c', 'baselib/api.c'],
		CFLAGS = ['-g', '-fcolor-diagnostics'], CC = 'clang')
src = Glob('client/example.c')
ipmc_client = env.Program('ipmc_client',
		src,
		LIBS = ['mongoose', 'pthread'],
        	LIBPATH = ['.'], 
		CFLAGS = ['-g'])

src = Glob('server/example.c')

ipmc_server = env.Program('ipmc_server',
		src,
		LIBS = ['mongoose', 'pthread'],
        	LIBPATH = ['.'], 
		CFLAGS = ['-g'])
