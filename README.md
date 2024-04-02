# data-compression-algorithms
**<u>data_simple.txt</u>** - This dataset contains letters and alphabets
with consecutive repeatedness. Example: aaaaabbbbbcccc

**<u>data_random.txt</u>** - This dataset includes letters and alphabets
generated randomly and with an equal probability of occurrence for each
character. Example: svdabmdo23

Along with data, **{abcdefghijklmnopqrstuvwxyz0123456789}** is the set
of characters I considered while creating the datasets. Both of the
datasets contain **10 million characters**.

Firstly, the **results for data_simple.txt**

<table style="width:100%;">
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 19%" />
<col style="width: 16%" />
<col style="width: 16%" />
<col style="width: 16%" />
</colgroup>
<thead>
<tr class="header">
<th></th>
<th><strong>Compression speed (MB/s)</strong></th>
<th><strong>Decompression speed (MB/s)</strong></th>
<th><strong>Compression Ratio</strong></th>
<th><strong>Memory Usage during Compression (KB)</strong></th>
<th><strong>Memory Usage during De-compression (KB)</strong></th>
</tr>
<tr class="odd">
<th><strong>Run length encoding algorithm</strong></th>
<th>3175.75</th>
<th>180.429</th>
<th>259.337</th>
<th>0</th>
<th>0</th>
</tr>
<tr class="header">
<th><strong>Dictionary Coder LZW algorithm</strong></th>
<th>4.49374</th>
<th>37.9599</th>
<th>247.299</th>
<th>2529.56</th>
<th>2529.5</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

Observing the values from the above table, it becomes clear that the
**run-length encoding algorithm performs better than the Dictionary
coder by a large margin**. It has far **better (de)compression speeds,
better compression ratio and almost 0 memory usage** (since it does not
store any dictionary or data during runtime apart from the given data).
Run length encoding algorithm is able to perform better because of the
fact that there is consecutive relatedness in data and the run length
algorithm is designed for this very fact.

However, results turn upside down when there are randomised data
patterns and consecutive repeatedness is removed.

Consider the following **results** from **data_random.txt**

<table style="width:100%;">
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 19%" />
<col style="width: 16%" />
<col style="width: 16%" />
<col style="width: 16%" />
</colgroup>
<thead>
<tr class="header">
<th></th>
<th><strong>Compression speed (MB/s)</strong></th>
<th><strong>Decompression speed (MB/s)</strong></th>
<th><strong>Compression Ratio</strong></th>
<th><strong>Memory Usage during Compression (KB)</strong></th>
<th><strong>Memory Usage during De-compression (KB)</strong></th>
</tr>
<tr class="odd">
<th><strong>Run length encoding algorithm</strong></th>
<th>176.993</th>
<th>8552.4</th>
<th>0.514291</th>
<th>0</th>
<th>0</th>
</tr>
<tr class="header">
<th><strong>Dictionary Coder LZW algorithm</strong></th>
<th>2.96384</th>
<th>82.4991</th>
<th>3.49742</th>
<th>178705</th>
<th>178704</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

Observing the table, it is evident that the **dictionary coder algorithm
is slower than run-length encoding but performs compression tasks
significantly better** than the run-length encoding algorithm, as
apparent by compression ratios. The **run-length algorithm fails to
compress the data**, whereas the dictionary coder algorithm does it
seamlessly.

Thus, the **run-length encoding algorithm works better when there is
consecutive repeatedness** in data but fails to work on data where
characters are randomly present without any visible pattern. It is
generally used to compress images, audio, and video.

However, the **dictionary coder-based LZW algorithm** works in either
case; it is **slower than the run-length algorithm but effective in
compressing the data**. **Dictionary-based algorithms are more
reliable** and were implemented in Unix systems.
