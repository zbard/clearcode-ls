
echo "## Building tags "
ctags -R ../../ClearCode ../../tags
echo "----------------------------------------------------------------------"

echo "## Deleting existing run file "
rm run
echo "----------------------------------------------------------------------"

echo "## Building obj - MEM_CHECK "
gcc -O3  \
../source/cc_ls_constraints.c \
../source/cc_ls_main.c \
../source/cc_ls_queue.c \
-I../source/include \
../utils/debug/xdebug.c  \
-I../utils/debug/include \
-I../utils/mem_check/include \
../platform/linux/cc_linux_display.c \
../platform/linux/cc_linux_file_walkthrough.c \
../platform/linux/cc_color.c \
../platform/linux/cc_strip_path.c \
-I../platform/include \
-o run
echo "----------------------------------------------------------------------"

