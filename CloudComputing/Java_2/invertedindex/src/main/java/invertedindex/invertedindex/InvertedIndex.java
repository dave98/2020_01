package invertedindex.invertedindex;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.FloatWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;

public class InvertedIndex {
	
	public static class bigrammerMapper  extends Mapper<Object, Text, Text, Text>{
		@Override
		public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
			String line = value.toString().replaceAll("[^\\p{Alnum}\\s]", "");
			String words[] = line.split(" "); //Conviertiendo las lineas en palabras
			String flag = "";
			for(String s : words) {
				flag = flag + s + "-";
			}
			
			
			if(words.length != 0) {
				for(int i = 0; i < words.length-1; i++) {
					if(words[i].matches("[a-zA-Z]+") && words[i+1].matches("[a-zA-Z]+")) {
					System.out.println(words[i] + "--" + words[i+1]);
					context.write(new Text(words[i]), new Text(words[i+1]));
					}
				}
			}
			else {
				System.out.println("avoided");
			}
		}		
	}
	

	
	public static class bigrammerReducer extends Reducer<Text, Text, Text, Text>{
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException{
			HashMap<String, Integer> val_map = new HashMap<String, Integer>();
			int in_here = 0;
			
			for(Text val : values) {
				String temp = val.toString();
				if(val_map == null || val_map.get(temp) == null) {
					val_map.put(temp, 1);
				}
				else {
					in_here = (int)val_map.get(temp);
					val_map.put(temp, in_here);
				}
			}
			
			Integer total = 0;
			
			for(String i : val_map.keySet()) {
				total = total + val_map.get(i);
			}
			
			String result = "Bigramas in: " + total.toString() + " ";
			for(String i : val_map.keySet()) {
				result = result + " "  + i + " = " + val_map.get(i);
			}
			
			context.write(key, new Text(result));
		}
	}
	
	public static class InvertedReducer extends Reducer<Text, Text, Text, Text>{
		@Override
		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException{
			HashMap<String, Integer> m = new HashMap<String, Integer>();
			int count = 0;
			
			for(Text t : values) { // Un key una palabra, Values son las direcciones de los documento en donde esta esa palabra
				String str = t.toString(); // t es una ruta de texto
				if(m!=null && m.get(str)!=null) {
					count=(int)m.get(str); // Si el archivo esta entonces extrae el valor asociado a las repeticiones con su palabra key
					m.put(str, ++count);   // Y termina sumándolo
				}
				else {
					m.put(str, 1);			// Si en caso no esta, lo registra como 1 (al ser el primer archivo asociado a esa palabra)
				}
			}
			String result = "0.1";
			for( String i : m.keySet()) {
				result = result + " " + i + "=" + m.get(i);
			}
			context.write(key,  new Text(result));	
		}
	}

	

	
	public static class pageRankMapper extends Mapper<Object, Text, Text, Text>{
		@Override
		public void map(Object key, Text value, Context context) throws IOException, InterruptedException{
			
			String line = value.toString();
			String words[] = line.split("\\s+");
			int n_words = words.length;
			
			float relevance = Float.parseFloat(words[1]); // El reducer anterior pone aqui la relevancia para dicha palabra
			
			//Starting to record recomendations
			// Starting a 2 'cause 2 previous values were already extracted
			float all_number_of_mentions = 0f;
			for(int i = 2; i < n_words; i++) {
				String getting[] = words[i].split("=");	
				all_number_of_mentions = all_number_of_mentions + Float.parseFloat(getting[1]);
			}
			
			for(int i = 2; i < n_words; i++) {
				String getting[] = words[i].split("="); // Getting has two values -> getting[0] = file_name, getting[1]= number of repition for "key" 
				Float share_relevance = relevance * (all_number_of_mentions / Float.parseFloat(getting[1])); 
				context.write(new Text(getting[0]), new Text( share_relevance.toString()) );
			}
		}
	}
	
	public static class pageRankReducer extends Reducer<Text, Text, Text, FloatWritable >{
		HashMap<Float, String> h_map = new HashMap<Float, String>();
	
		@Override
		public void reduce(Text key_filename, Iterable<Text> s_relevance, Context context) throws IOException, InterruptedException{
			Float temp = 0f; 
			for(Text t: s_relevance) {
				temp += Float.parseFloat(t.toString());
			}
			h_map.put(temp, key_filename.toString()); // Careful, associating one value to one file, wont work with two pages with same rank
			
		}
		
		@Override
		public void cleanup(Context context) throws IOException, InterruptedException {
			System.out.println("Page Rank indexing....");
			Set<Float> keys = new TreeSet<Float>(new Comparator<Float>() {
				@Override
				public int compare(Float o1, Float o2) {
					return o2.compareTo(o1);
				}
			});
			keys.addAll(h_map.keySet());
			
			for (Float k: keys) {
				context.write(new Text(h_map.get(k)) , new FloatWritable(k));
			}
		}
		
	}
	
	public class ConsoleColors {
	    // Reset
	    public static final String RESET = "\033[0m";  // Text Reset

	    // Regular Colors
	    public static final String BLACK = "\033[0;30m";   // BLACK
	    public static final String RED = "\033[0;31m";     // RED
	    public static final String GREEN = "\033[0;32m";   // GREEN
	    public static final String YELLOW = "\033[0;33m";  // YELLOW
	    public static final String BLUE = "\033[0;34m";    // BLUE
	    public static final String PURPLE = "\033[0;35m";  // PURPLE
	    public static final String CYAN = "\033[0;36m";    // CYAN
	    public static final String WHITE = "\033[0;37m";   // WHITE

	    // Bold
	    public static final String BLACK_BOLD = "\033[1;30m";  // BLACK
	    public static final String RED_BOLD = "\033[1;31m";    // RED
	    public static final String GREEN_BOLD = "\033[1;32m";  // GREEN
	    public static final String YELLOW_BOLD = "\033[1;33m"; // YELLOW
	    public static final String BLUE_BOLD = "\033[1;34m";   // BLUE
	    public static final String PURPLE_BOLD = "\033[1;35m"; // PURPLE
	    public static final String CYAN_BOLD = "\033[1;36m";   // CYAN
	    public static final String WHITE_BOLD = "\033[1;37m";  // WHITE

	    // Underline
	    public static final String BLACK_UNDERLINED = "\033[4;30m";  // BLACK
	    public static final String RED_UNDERLINED = "\033[4;31m";    // RED
	    public static final String GREEN_UNDERLINED = "\033[4;32m";  // GREEN
	    public static final String YELLOW_UNDERLINED = "\033[4;33m"; // YELLOW
	    public static final String BLUE_UNDERLINED = "\033[4;34m";   // BLUE
	    public static final String PURPLE_UNDERLINED = "\033[4;35m"; // PURPLE
	    public static final String CYAN_UNDERLINED = "\033[4;36m";   // CYAN
	    public static final String WHITE_UNDERLINED = "\033[4;37m";  // WHITE

	    // Background
	    public static final String BLACK_BACKGROUND = "\033[40m";  // BLACK
	    public static final String RED_BACKGROUND = "\033[41m";    // RED
	    public static final String GREEN_BACKGROUND = "\033[42m";  // GREEN
	    public static final String YELLOW_BACKGROUND = "\033[43m"; // YELLOW
	    public static final String BLUE_BACKGROUND = "\033[44m";   // BLUE
	    public static final String PURPLE_BACKGROUND = "\033[45m"; // PURPLE
	    public static final String CYAN_BACKGROUND = "\033[46m";   // CYAN
	    public static final String WHITE_BACKGROUND = "\033[47m";  // WHITE

	    // High Intensity
	    public static final String BLACK_BRIGHT = "\033[0;90m";  // BLACK
	    public static final String RED_BRIGHT = "\033[0;91m";    // RED
	    public static final String GREEN_BRIGHT = "\033[0;92m";  // GREEN
	    public static final String YELLOW_BRIGHT = "\033[0;93m"; // YELLOW
	    public static final String BLUE_BRIGHT = "\033[0;94m";   // BLUE
	    public static final String PURPLE_BRIGHT = "\033[0;95m"; // PURPLE
	    public static final String CYAN_BRIGHT = "\033[0;96m";   // CYAN
	    public static final String WHITE_BRIGHT = "\033[0;97m";  // WHITE

	    // Bold High Intensity
	    public static final String BLACK_BOLD_BRIGHT = "\033[1;90m"; // BLACK
	    public static final String RED_BOLD_BRIGHT = "\033[1;91m";   // RED
	    public static final String GREEN_BOLD_BRIGHT = "\033[1;92m"; // GREEN
	    public static final String YELLOW_BOLD_BRIGHT = "\033[1;93m";// YELLOW
	    public static final String BLUE_BOLD_BRIGHT = "\033[1;94m";  // BLUE
	    public static final String PURPLE_BOLD_BRIGHT = "\033[1;95m";// PURPLE
	    public static final String CYAN_BOLD_BRIGHT = "\033[1;96m";  // CYAN
	    public static final String WHITE_BOLD_BRIGHT = "\033[1;97m"; // WHITE

	    // High Intensity backgrounds
	    public static final String BLACK_BACKGROUND_BRIGHT = "\033[0;100m";// BLACK
	    public static final String RED_BACKGROUND_BRIGHT = "\033[0;101m";// RED
	    public static final String GREEN_BACKGROUND_BRIGHT = "\033[0;102m";// GREEN
	    public static final String YELLOW_BACKGROUND_BRIGHT = "\033[0;103m";// YELLOW
	    public static final String BLUE_BACKGROUND_BRIGHT = "\033[0;104m";// BLUE
	    public static final String PURPLE_BACKGROUND_BRIGHT = "\033[0;105m"; // PURPLE
	    public static final String CYAN_BACKGROUND_BRIGHT = "\033[0;106m";  // CYAN
	    public static final String WHITE_BACKGROUND_BRIGHT = "\033[0;107m";   // WHITE
	}

	static void Browser(String look_for, String InvertedLook, String PageRanked) {
		File folder = new File(InvertedLook);
		File[] list_of_invertex_result = folder.listFiles();
		
		List<String> located = new ArrayList<String>();
		List<Integer> total_references = new ArrayList<Integer>();
		List<Float> values = new ArrayList<Float>();

		for(File file : list_of_invertex_result) {
			if(file.isFile()) {
				try(BufferedReader br = new BufferedReader(new FileReader(file))){
					for(String line; (line = br.readLine()) != null; ) {
						String[] words_in_line = line.split("\\s+");
						
						if (words_in_line[0].equals(look_for)) {
							//System.out.println("INGRESO");
							int n_words = words_in_line.length;
							for(int i = 2; i < n_words; i++) {
								String[] get_file_name = words_in_line[i].split("=");
								located.add(get_file_name[0]);
								total_references.add(Integer.parseInt(get_file_name[1]));
							}
							break;
						}
					}
					
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
		
		if (located.size() == 0) {
			System.out.println("\t\tNada fue encontrado");
			return;
		}
		else {
			File page_folder = new File(PageRanked);
			File[] list_of_page_result = page_folder.listFiles();
			
			for(File file : list_of_page_result) {
				if(file.isFile()) {
					try(BufferedReader br = new BufferedReader(new FileReader(file))){
							
						for(String line; (line = br.readLine()) != null; ) {
							String[] words_in_line = line.split("\\s+");
							
							for (int i = 0; i < located.size(); i++) {
								if (words_in_line[0].equals(located.get(i))) {
									values.add(Float.parseFloat(words_in_line[1]));
								}
							}
							
						}
						
					} catch (FileNotFoundException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
			/*
			System.out.println(located.size() + " " + values.size());
			for(int i = 0; i < located.size(); i++) {
				System.out.println("L -->"+ located.get(i));
			}
			
			for(int i = 0; i < values.size(); i++) {
				System.out.println("S-->" + values.get(i));
			}*/
			
			if(located.size() !=  values.size()) {
				System.out.println("\t ERROR: Inconsistencia de Busqueda");
			}
			else {
				//System.out.println("\t La palabra " + ConsoleColors.RED + " " + look_for + " " + ConsoleColors.RESET + "fue encontrada en: ");
				System.out.println("\t La palabra " + look_for + " fue encontrada en: ");
				for(int i = 0; i < located.size(); i++) {
					System.out.println("\t\t" + located.get(i) + " un total de " + total_references.get(i) + " veces. " + " Page Rank de " + values.get(i) );
				}
			}
		}
		
	}
	
	public static void main(String[] args) throws Exception{
		
		/*
		//Auto-generated method stub
		//System.setProperty("hadoop.home.dir", "D:\\hadoop-2.8.3");
		*/
		
		System.out.println("Starting Inverted Index processing ---------------------------------");

		Configuration conf = new Configuration();
		Job job = Job.getInstance(conf, "InvertedIndex");
		
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setJarByClass(InvertedIndex.class);
		job.setMapperClass(bigrammerMapper.class);
		job.setReducerClass(bigrammerReducer.class);
		//job.setMapperClass(InvertedMapper.class);
		//job.setReducerClass(InvertedReducer.class);
		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(Text.class);
		job.setInputFormatClass(TextInputFormat.class);
		job.setOutputFormatClass(TextOutputFormat.class);
		
		Path InputinvertedIndex = new Path(args[0]);
		Path InputpageRank = new Path(args[1]);
		//Path OutputpageRank = new Path(args[2]);
		
		FileInputFormat.addInputPath(job, InputinvertedIndex);
		FileOutputFormat.setOutputPath(job, InputpageRank);
		
		//InputpageRank.getFileSystem(conf).delete(InputpageRank);
		
		boolean status = job.waitForCompletion(true);
		if(!status) {
			System.out.println("ERROR: Inverted Index failed");
			System.exit(1);
		}
		else {
			System.exit(0);
		}
		
		/*
		System.out.println("Inverted Index completed...");
		System.out.println("Starting Page Rank processing ---------------------------------");
		Job rank_job = Job.getInstance(conf, "PageRank");
		
		rank_job.setMapOutputKeyClass(Text.class);
		rank_job.setMapOutputValueClass(Text.class);
		rank_job.setJarByClass(InvertedIndex.class);
		rank_job.setMapperClass(pageRankMapper.class);
		rank_job.setReducerClass(pageRankReducer.class);
		
		rank_job.setOutputKeyClass(Text.class);
		rank_job.setOutputValueClass(FloatWritable.class);
		rank_job.setInputFormatClass(TextInputFormat.class);
		rank_job.setOutputFormatClass(TextOutputFormat.class);
		
		FileInputFormat.addInputPath(rank_job, InputpageRank);
		FileOutputFormat.setOutputPath(rank_job, OutputpageRank);
		status = rank_job.waitForCompletion(true);
		if(!status) {
			System.out.println("ERROR: Page Rank failed");
			System.exit(1);
		}
		System.out.println("Page Rank completed...");
		
		boolean start_looking_around = true;
		boolean continue_loking = true;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		
		if(!start_looking_around) {
			System.exit(0);
		}
		else {
			System.out.println("Starting Browser ---------------------------------");
			System.out.println("Welcome to COOCLE");
			while(continue_loking) {
				System.out.print("Type something: ");
				String finding_something = reader.readLine();
				if(finding_something.equals("exit")) {
					continue_loking = false;
				}else {
					System.out.println("\t Looking for " + finding_something);
					Browser(finding_something, args[1], args[2]);
				}
			}
			System.exit(0);
		}*/
		
	}
}
