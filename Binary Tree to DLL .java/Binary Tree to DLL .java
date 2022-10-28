
//User function Template for Java

/* class Node
class Node
{
	Node left, right;
	int data;
	
	Node(int d)
	{
		data = d;
		left = right = null;
	}
	
}*/

//This function should return head to the DLL
class Solution
{
    Node bToDLL(Node root)
    {
	    Queue<Node> q=new LinkedList<>();
	    Stack<Node> st=new Stack<>();
	    
        //code to get preorder traversal of Binary Tree
	    Node curr=root;
	    while(curr!=null || !st.isEmpty())
	    {
	        while(curr!=null)
	        {
	            st.push(curr);
	            curr=curr.left;
	        }
	        Node t=st.pop();
	        q.offer(t);
	        curr=t.right;
	    }
	    
	    
	   //code to form a doublly LinkedList
	   Node prev=null;
	   Node head=null;
	   
	    while(!q.isEmpty())
	    {
	        Node temp=q.poll();
	        temp.left=prev;
	        prev=temp;
	        Node next=q.peek();
	        temp.right=next;
	        if(head==null)
	        {
	            head=temp;
	        }
	    }
	    return head;
    }
}
