CYAN='\033[0;36m'
NC='\033[0m' # No Color

LARGE_DIM=150

mpic++ main.cpp
echo "---------------------- NEW RUN --------------------------"
echo -e "${CYAN}test run, 2 CPUs, 10x10 grid:${NC}"
mpirun -np 2 a.out 10 10
#echo -e "${CYAN}3. Random generated large matrix, 1 CPU:${NC}"
#mpirun -np 1 a.out ${LARGE_DIM}
#echo -e "${CYAN}4. Random generated large matrix, 2 CPUs:${NC}"
#mpirun -np 2 a.out ${LARGE_DIM}
echo "---------------------------------------------------------"
