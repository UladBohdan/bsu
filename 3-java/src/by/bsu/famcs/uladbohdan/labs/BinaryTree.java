package by.bsu.famcs.uladbohdan.labs;

import java.util.*;

public class BinaryTree<T extends Comparable<T>> {
    public BinaryTree() {
        this.depth = 0;
        this.selectElement = false;
    }

    public void add(T val) {
        TreeNode toAdd = new TreeNode(val);
        if (this.root==null) {
            this.root = toAdd;
            this.depth = 1;
            return;
        }
        TreeNode<T> temp = this.root;
        int curDepth = 1;
        while(true) {
            curDepth++;
            int cmp = val.compareTo(temp.value);
            if (cmp<0) {
                if (temp.left!=null)
                    temp = temp.left;
                else {
                    temp.left = toAdd;
                    break;
                }
            }
            else if (cmp>0) {
                if (temp.right!=null)
                    temp = temp.right;
                else {
                    temp.right = toAdd;
                    break;
                }
            }
            else
                break;
        }
        if (curDepth>this.depth)
            this.depth = curDepth;
    }
    public void add(T[] vals) {
        for (int i=0; i<vals.length; i++)
            add(vals[i]);
    }
    public void preOrderTraversal() {
        if (root==null) {
            System.out.println("tree is empty.");
            return;
        }
        preOrderTraversal(root);
        System.out.println();
    }
    public void inOrderTraversal() {
        if (root==null) {
            System.out.println("Tree is empty.");
            return;
        }
        inOrderTraversal(root);
        System.out.println();
    }
    public void postOrderTraversal() {
        if (root==null) {
            System.out.println("Tree is empty.");
            return;
        }
        postOrderTraversal(root);
        System.out.println();
    }
    public boolean search(T val) {
        return search(val, root);
    }
    public void showOnTree(T val) {
        if (search(val, root)==true) {
            System.out.println(val+" exists:");
            selectElement = true;
            valueToSelect = val;
            show();
        }
        else
            System.out.println("No item "+val+" in a tree.");
    }
    public boolean remove(T val) {
        return remove(val, root, null);
    }
    public boolean remove(T[] vals) {
        boolean ans = true;
        for (int i=0; i<vals.length; i++) {
            boolean temp = remove(vals[i]);
            if (!temp)
                ans = false;
        }
        return ans;
    }
    public int getDepth() {
        return this.depth;
    }
    public void show() {
        if (root==null) {
            System.out.println("tree is empty! have nothing to visualize.");
            return;
        }
        System.out.println("tree visualization:");
        StringBuilder str[] = new StringBuilder[depth];
        for (int i=0; i<depth; i++)
            str[i] = new StringBuilder();
        ArrayDeque<TreeNode<T>> queue = new ArrayDeque<>();
        queue.add(this.root);
        int curDepth=1;
        int toTake=1;
        TreeNode<T> nullNode = new TreeNode<>();
        while (curDepth<=this.depth) {
             String begin = getSpaces(width*(1<<(depth-curDepth-1))-width/2);
             str[curDepth-1].append(begin);
             for (int i=0; i<toTake; i++) {
                 TreeNode<T> temp = queue.getLast();
                 queue.removeLast();
                 if (temp==nullNode) {
                     str[curDepth - 1].append(getSpaces(width));
                     queue.push(nullNode);
                     queue.push(nullNode);
                 }
                 else {
                     if (temp.left==null)
                        queue.push(nullNode);
                     else
                        queue.push(temp.left);
                     if (temp.right==null)
                         queue.push(nullNode);
                     else
                        queue.push(temp.right);
                     str[curDepth - 1].append(nodeToString(temp));
                 }
                 String between = getSpaces(width*(1<<(depth-curDepth)) - width);
                 str[curDepth-1].append(between);
             }
             toTake*=2;
             curDepth++;
        }
        for (int d=0; d<depth; d++) {
            System.out.println(str[d]);
        }
        System.out.println();
    }

    private void preOrderTraversal(TreeNode<T> cur) {
        System.out.print(cur.value+" ");
        if (cur.left!=null)
            preOrderTraversal(cur.left);
        if (cur.right!=null)
            preOrderTraversal(cur.right);
    }
    private void inOrderTraversal(TreeNode<T> cur) {
        if (cur.left!=null)
            inOrderTraversal(cur.left);
        System.out.print(cur.value+" ");
        if (cur.right!=null)
            inOrderTraversal(cur.right);
    }
    private void postOrderTraversal(TreeNode<T> cur) {
        if (cur.left!=null)
            postOrderTraversal(cur.left);
        if (cur.right!=null)
            postOrderTraversal(cur.right);
        System.out.print(cur.value+" ");
    }
    private boolean search(T val, TreeNode<T> cur) {
        int cmp=val.compareTo(cur.value);
        if (cmp==0)
            return true;
        else if (cmp<0 && cur.left!=null)
            return search(val,cur.left);
        else if (cmp>0 && cur.right!=null)
            return search(val, cur.right);
        else
            return false;
    }
    private boolean remove(T val, TreeNode<T> cur, TreeNode<T> par) {
        int cmp = val.compareTo(cur.value);
        if (cur==null || (cmp!=0 && cur.left==null && cur.right==null))
            return false;
        if (cmp==0) {
            if (cur.left==null && cur.right==null) {
                if (par==null) {
                    root=null;
                    return true;
                }
                else {
                    if (par.left==cur)
                        par.left=null;
                    else if (par.right==cur)
                        par.right=null;
                    this.depth = updateTreeDepth(root);
                    return true;
                }
            }
            else if (cur.left==null) {
                TreeNode<T> rRight;
                rRight = cur.right;
                cur.value = rRight.value;
                cur.left = rRight.left;
                cur.right = rRight.right;
                return true;
            }
            else if (cur.right==null) {
                TreeNode<T> rLeft;
                rLeft = cur.left;
                cur.value = rLeft.value;
                cur.right = rLeft.right;
                cur.left = rLeft.left;
                return true;
            }
            else if (cur.right.left==null) {
                TreeNode<T> rRight = cur.right;
                cur.value = rRight.value;
                cur.right = rRight.right;
                return true;
            }
            else {
                TreeNode<T> parent = cur;
                TreeNode<T> temp = cur.right;
                while (temp.left!=null) {
                    parent = temp;
                    temp = temp.left;
                }
                cur.value = temp.value;
                parent.left=null;
            }
        }
        else if (cmp>0)
            return remove(val, cur.right, cur);
        else if (cmp<0)
            return remove(val, cur.left, cur);
        return false;
    }
    private int updateTreeDepth(TreeNode<T> cur) {
        if (cur==null)
            return 0;
        return ( Math.max(updateTreeDepth(cur.left), updateTreeDepth(cur.right)) +1);
    }
    private String nodeToString(TreeNode<T> x) {
        String color;
        if (selectElement && x.value==valueToSelect) {
            color = "[31m";
            selectElement = false;
        }
        else
            color = "[36m";
        String ans = (char)27+color;
        ans += x.value.toString();
        ans += (char)27+"[0m";
        while (ans.length()<width+9)
            ans+=" ";
        return ans;
    }
    private String getSpaces(int n) {
        StringBuilder str = new StringBuilder();
        for (int i=0; i<n; i++)
            str.append(' ');
        return str.toString();
    }

    private TreeNode<T> root;
    private int depth;
    private T valueToSelect;
    private boolean selectElement;
    private static final int width = 4; // both for data and spaces
}
