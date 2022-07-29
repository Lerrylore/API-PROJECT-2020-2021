# API-PROJECT-2020-2021

The development of this project is part of the algorithms and principles of informatics course at the Polytechnic University of Milan, and as a final examination, it is necessary for the bachelor's degree in computer engineering. The course was held by prof. Matteo Pradella, Davide Martinenghi and Alessandro Barenghi in the academic year 2020-2021 and the project was automatically evaluated by a proprietary platform of the DEIB (Department of Electronics, Information, Bioengineering) of the Polytechnic University of Milan.<br>
***Final score: 30/30 cum laude***

## Project specification

<img src="/assets/An-example-of-a-directed-graph-with-9-nodes.png" style="width:260px;height:130px;margin-left: 5px;" align="right">
<p>This project establishes a ranking of a set of weighted direct graphs provided as input. The score attributed to each graph is obtained from the sum of the shortest paths between the initial node and all the other nodes.</p>


<p>The program receives two parameters, from the command line, separated by a space:
  <ol>
    <li> <em>d </em>⁓ number of nodes of the graphs</li>
    <li> <em>k </em>⁓ length of the ranking</li>
  </ol>
</p>

<p>Supported commands:
  <ul>
    <li> 
      <p>
        <code>AggiungiGrafo [adjacency_matrix] </code>
      </p>
      <p>
        A graph is added to those considered to draw up the ranking. The command is
        followed by the adjacency matrix of the graph itself, inserted one row at a time,
        with elements separated by commas.
       </p>
    </li>
    <li> 
      <p>
        <code>TopK </code>
      </p>
      <p>
        The program prints the integer indices of the <em>k</em> graphs having the smallest 
        <em>k</em>values according to the previously described metric. If there are several 
        graphs with the same score, the first to arrive have priority.
      </p>
    </li>
  </ul>
</p>
<pre>
<b><i>Example of execution</i></b>
<code>
  >  <span>3,2</span>
  >  <span>AggiungiGrafo</span>
  >  <span>0,4,3</span>
  >  <span>0,2,0</span>
  >  <span>2,0,0</span>
  >  <span>AggiungiGrafo</span>
  >  <span>0,0,2</span>
  >  <span>7,0,4</span>
  >  <span>0,1,0</span>
  >  <span>AggiungiGrafo</span>
  >  <span>3,1,8</span>
  >  <span>0,0,6</span>
  >  <span>0,9,0</span>
  >  <span>TopK</span>
  <b>>></b> 0 1
 </code>
</pre>

## Compiling the program with GCC
1. Go to the folder where the source code file is stored
2. Compile the source code file typing: <code>gcc [program_name].c -o [executable_file_name]</code>
3. Run the newly compiled program typing: <code>./[executable_file_name]</code>

## Tools used
- **GCC + Ubuntu** - Development environment
- **Memcheck, AddressSaniter** - Memory error detector
- **Massif (Massif-visualizer)** - Allocated  memory visualizer
- **Callgrind (Kcachegrind)** - Execution time controller

