package by.bsu.famcs.uladbohdan.labs;

public class TreeNode<T extends Comparable<T>> {
    public T value;
    public TreeNode<T> left;
    public TreeNode<T> right;  // just if tree is binary

    public TreeNode() {
        this.value=null;
        this.left=null;
        this.right=null;
    }
    public TreeNode(T val) {
        this.value = val;
        this.left = null;
        this.right = null;
    }
}