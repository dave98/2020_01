package pagerank.pagerank;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.util.ToolRunner;

// Funcion para controlar toda la estructura de ejecución para PageRank
public class GrandController {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		ToolRunner.run(new Configuration(), args);
		
		int RankNumberExecutions = 40;
		for(int k = 0; k <  RankNumberExecutions; k++) {
			
		}
	}
	
	

}
ec2-user