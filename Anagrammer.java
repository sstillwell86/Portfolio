package org.apache.commons.cli;

public class Anagrammer {
	
	public static void main(String[] args) {
		Options options = new Options();
		options.addOption("words", "filter-words", false, "displays anagrams of supplied word that are also words");
		options.addOption("nf", "no-filter", false, "displays all possible permutations of the supplied word");
		options.addOption("a", "anagram", true, "Supplies the anagram to evaluate");
		options.addOption("h", "help", false, "displays the help for this program");
		HelpFormatter formatter = new HelpFormatter();
		CommandLineParser parser = new DefaultParser();
		try {
			CommandLine cmd = parser.parse( options, args);
			AnagramEvaluatorImpl anagrammer = new AnagramEvaluatorImpl();
			if(cmd.hasOption("h")) {
				formatter.printHelp( "ant", options );
			}
			if(cmd.hasOption("a")) {
				if(cmd.hasOption("words")) {
					String word = cmd.getOptionValue("anagram");
					if (word.equals(null)) {
						word = cmd.getOptionValue("a");
					}
					anagrammer.evaluate(word, "words");
				} else if (cmd.hasOption("nf")) {
					String word = cmd.getOptionValue("anagram");
					if (word.equals(null)) {
						word = cmd.getOptionValue("a");
					}
				    anagrammer.evaluate(word, "nf");
				} else {
					String word = cmd.getOptionValue("anagram");
					if (word.equals(null)) {
						word = cmd.getOptionValue("a");
					}
					anagrammer.evaluate(word, "words");
				}
			} else if (!cmd.hasOption("h")) {
				System.out.print("Missing required option: -a");
			}
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		
	}

}
