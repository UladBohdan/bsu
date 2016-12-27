CYAN='\033[0;36m'
NC='\033[0m' # No Color

SMALL_SIZE=15
LARGE_SIZE=100

mpic++ -std=c++11 mpi-poisson.cpp

echo "---------------------- NEW RUN --------------------------"
echo -e "${CYAN}1 CPU, small grid (${SMALL_SIZE}x${SMALL_SIZE}):${NC}"
mpirun -np 1 a.out ${SMALL_SIZE} ${SMALL_SIZE} 'small1.txt'
echo "---------------------------------------------------------"
echo -e "${CYAN}2 CPUs, small grid (${SMALL_SIZE}x${SMALL_SIZE}):${NC}"
mpirun -np 2 a.out ${SMALL_SIZE} ${SMALL_SIZE} 'small2.txt'
echo "---------------------------------------------------------"
echo -e "${CYAN}1 CPU, large grid (${LARGE_SIZE}x${LARGE_SIZE}):${NC}"
mpirun -np 1 a.out ${LARGE_SIZE} ${LARGE_SIZE} 'large1.txt'
echo "---------------------------------------------------------"
echo -e "${CYAN}2 CPUs, large grid (${LARGE_SIZE}x${LARGE_SIZE}):${NC}"
mpirun -np 2 a.out ${LARGE_SIZE} ${LARGE_SIZE} 'large2.txt'
echo "---------------------------------------------------------"
