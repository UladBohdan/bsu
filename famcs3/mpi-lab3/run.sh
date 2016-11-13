CYAN='\033[0;36m'
NC='\033[0m' # No Color

LARGE_DIM=150

mpic++ main.cpp
echo "---------------------- NEW RUN --------------------------"
echo $'Checking if everything works well for small matrixes...'
echo -e "${CYAN}1. 2x2 matrix:${NC}"
mpirun -np 2 a.out 2 matrix0.txt
echo -e "${CYAN}2. 3x3 matrix:${NC}"
mpirun -np 2 a.out 3 matrix1.txt
echo -e "${CYAN}3. Random generated large matrix, 1 CPU:${NC}"
mpirun -np 1 a.out ${LARGE_DIM}
echo -e "${CYAN}4. Random generated large matrix, 2 CPUs:${NC}"
mpirun -np 2 a.out ${LARGE_DIM}
echo "---------------------------------------------------------"
