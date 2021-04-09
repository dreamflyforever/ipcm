gcc ../server/mongoose.c pub.c api.c -I ../server -o pub -lpthread
gcc ../server/mongoose.c sub.c api.c -I ../server -o sub -lpthread
