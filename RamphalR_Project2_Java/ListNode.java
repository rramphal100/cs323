public class ListNode {
	private int data;
	private ListNode next;
	
	public ListNode(){
		data = 0;
		next = null;
	}
	
	public ListNode(int n){
		data = n;
		next = null;
	}
	
	public int getData(){
		return data;
	}
	
	public ListNode getNext(){
		return next;
	}
	
	public void setNext(ListNode n){
		next = n;
	}
}

