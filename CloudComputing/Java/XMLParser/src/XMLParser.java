import java.io.IOException;
import java.nio.charset.CharacterCodingException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.hadoop.conf.Configuration;  //new
import org.apache.hadoop.fs.FSDataInputStream; //new
import org.apache.hadoop.io.DataOutputBuffer; //new 
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.InputSplit;
import org.apache.hadoop.mapreduce.TaskAttemptContext;
import org.apache.hadoop.mapreduce.lib.input.FileSplit;

public class XMLParser {

	public class XmlInputFormat extends TextInputFormat{
		
		public static final String START_TAG_KEY = "xmlinput.start";
		public static final String END_TAG_KEY = "xmlinput.end";
		
		@Override
		public RecordReader<LongWritable, Text> createRecordReader(InputSplit split, TaskAttemptContext context){
			try {
				return new XmlRecordReader((FileSplit) split, context);
			} catch(IOException e) {
				throw new RuntimeException("TODO: refactor this...");
			}
		}
		

		public static class XmlRecordReader extends RecordReader<LongWritable, Text>{
			private final byte[] startTag;
			private final byte[] endTag;
			private final long start;
			private final long end;
			private final FSDataInputStream fsin;
			private final DataOutputBuffer buffer = new DataOutputBuffer();
			
			private LongWritable key = new LongWritable();	
			private Text value = new Text();
			
			public XmlRecordReader(FileSplit split, TaskAttemptContext context) throws IOException{
				Configuration conf = context.getConfiguration();
				
			}
			
		}
		
	}
	
	
	public static class PageMapper extends Mapper<LongWritable, Text, Text, Text>{
		
		private final Pattern linksPattern = Pattern.compile("\\[.+?\\]");
		
		public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException{
			
			//Devuelve String[0] = <title>[TITLE]</title>
			//		   String[1] = <text>[CONTENT]</text>
			// sin los tags <>
			String[] titleAndText = parseTitleAndText(value);
		
			String pageString = titleAndText[0];
			if(notValidPage(pageString)) {
				return;
			}
			
			Text page = new Text(pageString.replace(' ', '_'));
			Matcher matcher = linksPattern.matcher(titleAndText[1]);

			while(matcher.find()) {
				String otherPage = matcher.group();
				//Filter only wiki pages.
				otherPage = getPageFromLink(otherPage);
				if(otherPage == null || otherPage.isEmpty())
					continue;
				
				context.write(page, new Text(otherPage));
			}
		}
		
		private String[] parseTitleAndText(Text value) throws CharacterCodingException{

			String[] titleAndText = new String[2];
			
			int start = value.find("<title>");
			int end = value.find("</title>", start); //Finds any occurence of what in the backing buffer, starting as position start.
			start += 7; // Añadiendo <title> al tamaño
			
			titleAndText[0] = Text.decode(value.getBytes(), start, end-start);
			
			start = value.find("<text");
			start = value.find(">", start);
			end = value.find("</text>", start);
			start += 1;

			if(start == -1 || end == -1) {
				return new String[] {"", ""};
			}
			
			titleAndText[1] = Text.decode(value.getBytes(), start, end-start);
			return titleAndText;		
		}
		
		private boolean notValidPage(String pageString) {
			return pageString.contains(":");
		}
	
		private String getPageFromLink(String alink) {
			if(isNotLink(alink)) return null;
			
			int start = alink.startsWith("[[") ? 2 : 1;
			int endlink = alink.indexOf("]");
			
			int pipePosition = alink.indexOf("|");
			if(pipePosition > 0) {
				endlink = pipePosition;
			}
			
			int part = alink.indexOf("#");
			if(part > 0) {
				endlink = part;
			}
			
			alink = alink.substring(start, endlink);
			alink = alink.replaceAll("\\s", "_");
			alink = alink.replaceAll(",", "");
			alink = sweetify(alink);
			
			return alink;
		}
		
		private boolean isNotLink(String alink) {
			int start = 1;
			if(alink.startsWith("[[")) {
				start = 2;
			}
			
			if(alink.length() < start+2 || alink.length() > 100) return true;
			char firstChar = alink.charAt(start);
			
			if(firstChar == '#') return true;
			if(firstChar == ',') return true;
			if(firstChar == '.') return true;
			if(firstChar == '&') return true;
			if(firstChar == '\'') return true;
			if(firstChar == '-') return true;
			if(firstChar == '{')  return true;
			
			if(alink.contains("s")) return true;
			if(alink.contains(",")) return true;
			if(alink.contains("&")) return true;
			
			return false;
		}
	
		private String sweetify(String aLinkText) {
			if(aLinkText.contains("&amp;")) {
				return aLinkText.replace("&amp", "&");
			}
			return aLinkText;
		}
	}
	
	public static class LinksReducer extends Reducer<Text, Text, Text, Text>{
		
		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException{
			String pagerank = "1.0\t";
			boolean first = true;
			
			for(Text value :values) {
				if(!first) pagerank += ",";
				pagerank += value.toString();
				first = false;
			}
			context.write(key, new Text(pagerank));
		}
	}
	
	
	
}
