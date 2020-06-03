package mapreduce.mapreduce;

import java.io.IOException;
import java.util.Iterator;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;


public class WordCount {

	public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable>{
		
		// Map receive two inputs, key and the actual line (value)
		// Now we need to breaking up our input and spitting it out to our context
		public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
			StringTokenizer st = new StringTokenizer(value.toString());
			Text WordOut = new Text(); // Output Key
			IntWritable one = new IntWritable(1); //Output value
			
			while(st.hasMoreTokens()) {
				WordOut.set(st.nextToken());
				context.write(WordOut, one); 
			} 
		}
	}
	 
	//First two variables in Reducer template must be equal to last two variables in Mapper template
	public static class SumReducer extends Reducer<Text, IntWritable, Text, IntWritable>{
		
		// term at the head of the list
		// Aggregated from previous 'one'
		public void reduce(Text term, Iterable<IntWritable> ones, Context context) throws IOException, InterruptedException {
			int count = 0;
			Iterator<IntWritable> iterator = ones.iterator();
			
			while(iterator.hasNext()) {
				count++;
				iterator.next();
			}
			IntWritable output = new IntWritable(count); 
			context.write(term, output);
		}
	} 
	
	public static void main(String[] args) throws Exception {
		//Auto-generated method stub
		//System.setProperty("hadoop.home.dir", "D:\\hadoop-2.8.3");
		
		Configuration conf = new Configuration();
		String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
		
		if(otherArgs.length != 2) {
			System.err.println("Usage: WordCount<input_file> <output_directory>");
			System.exit(2);
		}
		
		Job job = Job.getInstance(conf, "Word Count");
		job.setJarByClass(WordCount.class);
		job.setMapperClass(TokenizerMapper.class);
		job.setReducerClass(SumReducer.class);
		job.setNumReduceTasks(10);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		
		FileInputFormat.addInputPath(job, new Path(otherArgs[0]));
		FileOutputFormat.setOutputPath(job, new Path(otherArgs[1]));
		boolean status = job.waitForCompletion(true);
		if(status) {
			System.exit(0);
		}
		else {
			System.exit(1);
		}
				
	}
}
 