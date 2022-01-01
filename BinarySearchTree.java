import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


public class BinarySearchTree<E extends Comparable<E>> {

	protected TreeNode<E> root;
	protected int size = 0;
	
	public BinarySearchTree() { }
	
	public BinarySearchTree(E[] objects) {
		for (int i=0; i<objects.length; i++) {
			insert(objects[i]);
		}
	}
	
	public boolean search(E e) {
		TreeNode<E> current = root;
		
		while (current != null) {
			if (e.compareTo(current.element) < 0) {
				current = current.left;
			} else if (e.compareTo(current.element) > 0) {
				current = current.right;
			} else {
				return true;
			}
		}
		
		return false;
	}
	
	public boolean insert(E e) {
		if (root == null) {
			root = createNewNode(e);
		} else {
			TreeNode<E> parent = null;
			TreeNode<E> current = root;
			while (current != null) {
				if (e.compareTo(current.element) < 0) {
					parent = current;
					current = current.left;
				} else if (e.compareTo(current.element) > 0) {
					parent = current;
					current = current.right;
				} else {
					return false;
				}
			}
				
			if (e.compareTo(parent.element) < 0) {
				parent.left = createNewNode(e);
			} else {
				parent.right = createNewNode(e);
			}
		}
		
		size++;
		return true;
	}
	
	protected TreeNode<E> createNewNode(E e) {
		return new TreeNode<E>(e);
	}
	
	public void inorder() {
		inorder(root);
	}
	
	protected void inorder(TreeNode<E> root) {
		if (root == null) return;
		inorder(root.left);
		System.out.print(root.element + " ");
		inorder(root.right);
	}
	
	public void postorder() {
		postorder(root);
	}
	
	protected void postorder(TreeNode<E> root) {
		if (root == null) return;
		postorder(root.left);
		postorder(root.right);
		System.out.print(root.element + " ");
	}
	
	public void preorder() {
		preorder(root);
	}
	
	protected void preorder(TreeNode<E> root) {
		if (root == null) return;
		System.out.print(root.element + " ");
		preorder(root.left);
		preorder(root.right);
	}
	public ArrayList<E> breadthFirstTraversal(TreeNode<E> root) {
		ArrayList<E> list = new ArrayList<E>();
		if (root == null) return list;
		Queue<TreeNode<E>> queue = new LinkedList<TreeNode<E>>();
		queue.add(root);
		while(!queue.isEmpty()){
	        TreeNode<E> node = queue.remove();
	        System.out.print(node.element + " ");
	        list.add(node.element);
	        if(node.left != null) queue.add(node.left);
	        if(node.right != null) queue.add(node.right);
	    }
		return list;
	}
	
	public ArrayList<E> inorderTraversal(TreeNode<E> root) {
		Stack<TreeNode<E>> stack = new Stack<TreeNode<E>>();
		ArrayList<E> list = new ArrayList<E>();
		while (true) {
			while (root != null) {
				stack.push(root);
				root = root.left;
			}
			if (stack.isEmpty()) {
				return list;
			}
			root = stack.pop();
			System.out.print(root + " ");
			list.add(root.element);
			root = root.right;
		}
	}
	
	public int height(TreeNode<E> root) {
		if (root == null) return -1;
		int totalHeight;
		int leftHeight = height(root.left);
	    int rightHeight = height(root.right);
	    if (leftHeight > rightHeight) {
	    	totalHeight = leftHeight;
	    } else { 
	    	totalHeight = rightHeight;
	    }
	    return 1 + totalHeight;
	}
	
	public int getSize() {
		return size;
	}
	
	public TreeNode<E> getRoot() {
		return root;
	}
	
	public ArrayList<TreeNode<E>> path(E e) {
		ArrayList<TreeNode<E>> list = new ArrayList<>();
		TreeNode<E> current = root;
		
		while (current != null) {
			list.add(current);
			if (e.compareTo(current.element) < 0) {
				current = current.left;
			} else if (e.compareTo(current.element) > 0) {
				current = current.right;
			} else {
				break;
			}
		}
		
		return list;
	}
	
	public boolean delete(E e) {
		TreeNode<E> parent = null;
		TreeNode<E> current = root;
		
		while (current != null) {
			if (e.compareTo(current.element) < 0) {
				parent = current;
				current = current.left;
			} else if (e.compareTo(current.element)> 0) {
				parent = current;
				current = current.right;
			} else {
				break;
			}
		}
		
		if (current == null) {
			return false;
		}
		
		if (current.left == null) {
			if (parent == null) {
				root = current.right;
			} else {
				if (e.compareTo(parent.element) < 0) {
					parent.left = current.right;
				} else {
					parent.right = current.right;
				}
			}
		} else {
			TreeNode<E> parentOfRightMost = current;
			TreeNode<E> rightMost = current.left;
			
			while (rightMost.right != null) {
				parentOfRightMost = rightMost;
				rightMost = rightMost.right;
			}
			
			current.element = rightMost.element;
			
			if (parentOfRightMost.right == rightMost) {
				parentOfRightMost.right = rightMost.left;
			} else {
				parentOfRightMost.left = rightMost.left;
			}
		}
		
		size--;
		return true;
	}
	
	public Iterator<E> iterator() {
		return new InorderIterator();
	}
	
	public void clear() {
		root = null;
		size = 0;
	}
	
	
	private class InorderIterator implements Iterator<E> {
		
		private ArrayList<E> list = new ArrayList<>();
		private int current = 0;
		
		public InorderIterator() {
			inorder();
		}
		
		private void inorder() {
			inorder(root);
		}
		
		private void inorder(TreeNode<E> root) {
			if (root == null) return;
			inorder(root.left);
			list.add(root.element);
			inorder(root.right);
		}
		
		public boolean hasNext() {
			return current < list.size();
		}
		
		public E next() {
			return list.get(current++);
		}
		
		public void remove() {
			delete(list.get(current));
			list.clear();
			inorder();
		}
	}
}
