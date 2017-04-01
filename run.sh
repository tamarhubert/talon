_pwd=$(pwd)

paths[0]=lib/linkedListLibrary/lib/threadingProcessingLibrary/src
paths[1]=lib/linkedListLibrary/src
paths[2]=lib/threadingProcessingLibrary/src
paths[3]=lib/runtimeLinkingLibrary/src
paths[4]=modules/coreApi/src
paths[5]=modules/coreCli/src

for i in {0..5}
do
    echo
    cd ${paths[i]}
    rm -r bin
    mkdir bin
    rm -r ../obj
    mkdir ../obj
    make
    cd "$_pwd"
done

rm -r bin
mkdir bin
rm -r obj
mkdir obj

make
