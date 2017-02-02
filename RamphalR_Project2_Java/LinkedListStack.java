public class LinkedListStack{
	private ListNode top;
	
	public LinkedListStack(){
		top = null;
	}
	
	public void push(int in){
		ListNode temp = new ListNode(in);
		temp.setNext(top);
		top = temp;
		System.out.println("New Data: " + top.getData() + ", Next Node: " + top.getNext());
	}
	
	public boolean isEmpty(){
		return top == null;
	}
	
	public int pop(){
		if(isEmpty()){
			return 0;
		}
		int temp = top.getData();
		top = top.getNext();
		return temp;
	}
}
