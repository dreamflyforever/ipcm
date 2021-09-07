env = Environment(CPPPATH = ['baselib', 'client', 'server'])

#env.Library('uplib',src, CFLAGS = ['-g', '-lpthread'])
env.SharedLibrary('ipcm', ['baselib/mongoose.c', 'baselib/api.c'],
		CFLAGS = ['-g', '-fcolor-diagnostics'], CC = 'clang')
src = Glob('client/example.c')
ipcm_client = env.Program('ipcm_client',
		src,
		LIBS = ['ipcm', 'pthread'],
        	LIBPATH = ['.'], 
		CFLAGS = ['-g'])

src = Glob('server/example.c')

ipcm_server = env.Program('ipcm_server',
		src,
		LIBS = ['ipcm', 'pthread'],
        	LIBPATH = ['.'], 
		CFLAGS = ['-g'])
