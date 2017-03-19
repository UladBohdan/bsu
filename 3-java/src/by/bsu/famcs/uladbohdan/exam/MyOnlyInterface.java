package by.bsu.famcs.uladbohdan.exam;

import com.sun.istack.internal.NotNull;

public interface MyOnlyInterface {

    int methodToRealize();
    double oneMoreMethod(int a, String b);

    int G = 5;
}

interface MySecondInterface extends MyOnlyInterface {
    String lolMethod();
}

class RealizingMyInterface implements MySecondInterface {
    @Override
    public int methodToRealize() {
        return MyOnlyInterface.G;
    }

    @Override
    public double oneMoreMethod(int a, String b) {
        return 0;
    }

    @Override
    public String lolMethod() {
        return null;
    }
}
