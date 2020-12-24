import java.util.*;

class Graph{
	private int nodeSize;
	private ArrayList<Integer> next, to;
	private ArrayList<Long> cap;
	private int[] head, cur, depth;
	public Graph(int nodeSize) {
		this.nodeSize = nodeSize;
		next = new ArrayList<>();
		cap = new ArrayList<>();
		head = new int[nodeSize +1];
		to = new ArrayList<>();
		cur = new int[nodeSize + 1];
		depth = new int[nodeSize + 1];
		
		next.add(0);next.add(0);
		cap.add(0L);cap.add(0L);
		to.add(0);to.add(0);
	}
	public void addEdge(int x,int y,long c) {
		next.add(head[x]);
		head[x] = next.size() - 1;
		to.add(y);
		cap.add(c);
		
		next.add(head[y]);
		head[y] = next.size() - 1;
		to.add(x);
		cap.add(0L);
	}
	private boolean bfs(int S, int T) {
		for(int i = 1; i <= nodeSize ; i++) {
			depth[i] = -1;
		}
		depth[S] = 1;
		LinkedList<Integer> Q = new LinkedList<>();
		Q.add(S);
		while(Q.size() >= 1) {
			int now = Q.pollFirst();
			for(int i=head[now]; i != 0; i = next.get(i)) {
				if(depth[to.get(i)] == -1 && cap.get(i) > 0) {
					depth[to.get(i)] = 1 + depth[now];
					Q.add(to.get(i));
				}
			}
		}
		return depth[T]!=-1;
	}
	
	private long dfs(int T,int x,long mxfl) {
		if(x == T)return mxfl;
		long w = 0;
		for(int i=cur[x];i != 0; i=next.get(i)) {
			long used = 0;
			if(depth[to.get(i)] == depth[x] + 1){
				used = dfs(T, to.get(i), Math.min(mxfl-w, (long)cap.get(i)));
				long tmp = cap.get(i);
				cap.set(i, tmp-used);
				tmp = cap.get(i^1);
				cap.set(i^1, tmp+used);
				w += used;
				if(cap.get(i) > 0) cur[x] = i;
				if(w == mxfl)return mxfl;
			}
		}
		return w;
	}
	public long maxFlow(int S, int T) {
		long flow = 0;
		while(bfs(S, T)) {
			for(int i = 1; i <= nodeSize ; i ++) {
				cur[i] = head[i];
			}
			long tmp = dfs(T, S, 0x7fffffffffffffffL);
			flow += tmp;
		}
		return flow;
	}
}
public class Main {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n,m, S, T;
		n = sc.nextInt();
		m = sc.nextInt();
		S = sc.nextInt();
		T = sc.nextInt();
		Graph g = new Graph(n);
		for(int i=1;i<=m;i++) {
			int a,b,c;
			a = sc.nextInt();
			b = sc.nextInt();
			c = sc.nextInt();
			g.addEdge(a, b, c);
		}
		System.out.println(g.maxFlow(S, T));
	}
}