echo ""
echo "Basic"
echo ""
cd lab1-random-generator || exit 1
bash run.sh | grep "\(PASSED\|RUN\|FAILED\)" || exit 1

echo ""
echo "Discrete"
echo ""
cd ../lab2-discrete-random-variable || exit 1
bash run.sh | grep "\(PASSED\|RUN\|FAILED\)" || exit 1

echo ""
echo "Continuous"
echo ""
cd ../lab3-continuous-distributions || exit 1
bash run.sh | grep "\(PASSED\|RUN\|FAILED\)" || exit 1
