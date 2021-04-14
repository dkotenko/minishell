import os

path =os.path.abspath(os.getcwd())
#we shall store all the file names in this list
filelist = []


# sed -i -e '/s/(^[a-zA-Z]+)(\t{1,})(.*)(\(.*\)\n)/$1\t$3$4/g'
# (^[a-zA-Z]+)(\t{1,})(.*)(\(.*\)\n)
# $1\t$3$4


for root, dirs, files in os.walk(path):
	for file in files:
		if file[-2:] == ".c" or file[-2:] == ".h":
        #append the file name to the list
			filelist.append(os.path.join(root,file))

#print all the file names
for name in filelist:
    print(name)