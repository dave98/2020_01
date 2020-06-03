package sandbox.hadoop;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

import sandbox.hadoop.job1.xmlhakker.WikiLinksReducer;
import sandbox.hadoop.job1.xmlhakker.WikiPageLinksMapper;
import sandbox.hadoop.job1.xmlhakker.XmlInputFormat;

public class WikiPageRanking extends Configured implements Tool {
	
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		System.setProperty("hadoop.home.dir", "D:\\hadoop-2.8.3");  // Windows test delete this line before sending to servers
		System.exit(ToolRunner.run(new Configuration(), new WikiPageRanking(), args));
	}
	
	@Override
	public int run(String[] args) throws Exception{
		//boolean isCompleted = runXmlParsing("wiki/in", "wiki/ranking");
		boolean isCompleted = runXmlParsing(args[0], args[1]);
		if(!isCompleted) return 1;
		return 0;
	}
	 
	public boolean runXmlParsing(String inputPath, String outputPath) throws IOException, ClassNotFoundException, InterruptedException{
		System.out.println("Starting xmlParsing with " + inputPath + " " + outputPath);
		
		Configuration conf = new Configuration();
		//conf.set(XmlInputFormat.START_TAG_KEY, "<page>");
		//conf.set(XmlInputFormat.END_TAG_KEY, "</page>");
		
		Job xmlHakker = Job.getInstance(conf, "xmlHakker");
		xmlHakker.setJarByClass(WikiPageRanking.class);
		
		//Input - Mapper
		FileInputFormat.addInputPath(xmlHakker, new Path(inputPath));
		xmlHakker.setInputFormatClass(XmlInputFormat.class);  //--
		xmlHakker.setMapperClass(WikiPageLinksMapper.class);  //--
		xmlHakker.setMapOutputKeyClass(Text.class); // Dont get it...
		
		//Output - Reducer
		FileOutputFormat.setOutputPath(xmlHakker, new Path(outputPath));
		xmlHakker.setOutputFormatClass(TextOutputFormat.class);
		xmlHakker.setOutputKeyClass(Text.class);  //--
		xmlHakker.setOutputValueClass(Text.class); //--
		xmlHakker.setReducerClass(WikiLinksReducer.class);  //--
		
		
		//return xmlHakker.waitForCompletion(true);
		boolean status = xmlHakker.waitForCompletion(true);
		if(status) {
			System.out.println("XML Parser finalizado con exito");
			//System.exit(0);
			return true;
		}
		else {
			System.out.println("XML Parser Error");
			//System.exit(1);
			return false;
		}
				
	}

}
