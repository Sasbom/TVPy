# TVPy documentation
Documentation v0.1 - Work in progress. | [Head back to Readme](../README.md)

**Important Warning: Currently the core library only supports "TVPaint compressed" files. Non Compressed file support is coming in the future.** 

TVpy offers bindings to [TVPP_PP](https://github.com/Sasbom/TVPP_PP), a C++ library that is designed to quickly parse metadata from TVPaint files (*.tvpp)
and read out image buffers. It memory maps the file and represents the TVPaint file in a view-only state, parsing the image data only when it is needed.

The TVPy python module offers binding to all important "segments" of a TVPaint file, as well as extensive annotation.
Almost all python class definitions include a formatted `__str__`report of all of the internally cached variables. 
<br>This report is generated using C++,
so it's much faster than templating a whole f-string. 

### A general overview:

```py
import TVPy

# Initizalize mapped memory and parse.
tvp = TVPy.TvpFile("my_tvpaint_file.tvpp") 

# Print out the TvpFileInfo readout.
print(str(tvp.info)) # -> TvpFileInfo

tvp.close() # deinitialize and unmap memory.
```
Some classes like `TvpFile` and `TvpLayer` both support context management.
```py
import TVPy

with TVPy.TvpFile("my_tvpaint_file.tvpp") as tvp:
    # Print out the TvpFileInfo readout.
    print(str(tvp.info)) # -> TvpFileInfo
```

#### Hiearchy:
A TVPaint file (before 12.0) has a certain hierarchy:

`TvpFile -> TvpClip -> TvpLayer -> Frame`

- TvpFile
  - TvpFileInfo (Accessible through TvpFile.info)
  - TvpClip (Accessible through TvpFile.clips)
    - TvpLayer (Accessible through TvpClip.layers)
      - Frame data at time (top layer needs to be cached first.)
    - TvpLayer
      - Frame data at time
  - TvpClip
    - TvpLayer
      - Frame data at time

#### TvpFileInfo

`TvpFileInfo` contains file wide information.
The information that is most useful is the information pertaining to the document:

- `TvpFileInfo.width -> int` | File width
- `TvpFileInfo.height -> int` | File height
- `TvpFileInfo.fps -> float` | File Frames per second
- `str(TvpFileInfo)` | Summarize all file info. 

#### Clips and Layers:

Clips contain, most importantly:
- Mark in / Mark out times + whether mark in / mark out is active <br>`TvpClip.mark_in: bool`; `TvpClip.mark_in_pos: int`<br>`TvpClip.mark_out: bool`; `TvpClip.mark_out_pos: int`
- Layers: `TvpClip.layers -> List[TvpLayer]`

Layers contain all properties you'd want, blend modes, repeat in/out type. Consult the TVPy.pyi file for all the things a layer holds.

To use Layers with images, it is recommended that NumPy and PIL are installed;
<br>`pip install numpy pillow`

The python bindings for TVPy spit out numpy array types that are directly able to be used with PIL.

Consider a TVPaint File with the following structure:
- TvpFile("my_cool_anim.tvpp")
  - TvpClip
    - TvpLayer

We can use it with TVPy as follows:

```py
import TVPy
import numpy as np
from PIL import Image
# Initizalize mapped memory and parse.
tvp = TVPy.TvpFile("my_cool_anim.tvpp") 

clip = tvp.clips[0] # -> TvpClip
print(f"Accessing first clip {clip.name}!")

layer = clip.layers[0] # -> TvpLayer
print(f"Caching layer {layer.name}")
layer.cache_layer() # We cache the entire layer.
print("Cached layer!")

# Get frame 1. (generally TVPaint starts at 1.)
frame = layer.get_frame(1) # -> np.ndarray[[height, width, 4 (RGBA)], np.dtype.uint8]
print("Grabbed frame 1!")

img = Image.fromarray(frame) # -> PIL.Image
img.save("image_1.png")
print("Saved frame 1!")

layer.release_layer() # Manually free up cache space.
print("Released layer cache.")

tvp.close() # deinitialize and unmap memory.
print("Donezo!")
```
Alternatively, we can use direct indexing and context managers to handle all the kerfuffle around caching the layer and closing for us.<br>
This makes it MUCH more pleasant to look at the code. Thanks to the included pyi file, you should have no trouble using this.
```py
import TVPy
import numpy as np
from PIL import Image

with TVPy.TvpFile("my_cool_anim.tvpp") as tvp:
    with tvp[0][0] as layer:                    # Index clip 0, layer 0. (first clip, first layer.)
        img = Image.fromarray(layer[1])         # Directly convert to PIL Image.
        img.save("image_1.png")                 # Save.
                                                # Exit context managers and let cleanup happen automatically.
print("Donezo!")
```
**NOTE:**
Pre and Post behavior is correctly taken into account in both get_frame and the direct `__getitem__` (`[i]`) indexing.
<br>You can index beyond or before a frame range and be fine. Pythons default behavior for negative indices is dropped in favor of following TVPaints pre/post behavior.
<br>You can query the behavior with `TvpLayer.repeat_in_type` and `TvpLayer.repeat_out_type`


**Inherent Drawback: We can't cache only a single frame.**
<br>TVPaint's save format has built in "lookback", meaning that certain parts of an image that repeat across the timeline can be "referenced" from earlier.<br>
(Lets say, you have a background filled with the same color red, and only change a single pixel in 1 frame, most of the image data will "refer" back to the previous frame.)<br>
I wish things were different, but they aren't, so bear with it. Caching should be O(n) / linear time at worst if no references are present.

#### Demo: Caching out an entire file:
(Note that I'm avoiding layer names in files, as they might contain illegal characters pertaining to your operating system.)
```py
import TVPy
import numpy as np
from PIL import Image
from pathlib import Path

base_file = Path("./my_tobecached_file.tvpp")

with TVPy.TvpFile(basefile) as tvp:
    for clip_idx, clip in enumerate(tvp.clips):
        print(f"Processing clip {clip.name}!")
        clip_dir = base_file.parent / f"clip_{clip_idx}"
        clip_dir.mkdir(parents=True, exist_ok=True)
        
        for layer_idx, layer in enumerate(clip.layers):
            # Calculate layer framerange.
            start_frame = layer.frame_offset + 1 # 0 here means frame 1 in tvpaint.
            end_frame = start_frame + layer.frame_amount
            layer_dir = clip_dir / f"layer_{layer_idx}"
            layer_dir.mkdir(parents=True, exist_ok=True)
            print(f"Writing out layer {layer.name}, {start_frame} -> {end_frame}")
            with layer:
                for frame in range(start_frame, end_frame + 1): # range is non_inclusive for end
                    img = Image.fromarray(layer[frame])
                    img.save(layer_dir / f"layer{layer_idx}_{frame:0>4}.png")

print("Cached out", basefile, "!")
```

We traverse the file contents and let the context managers do the heavy lifting.

#### Closing statements:
Please use this library responsibly, and enjoy life.
Some things might not be too clear in this documentation. <br>

Note that the emphasis of this python library was primarily to read out metadata;<br>
That's how I'm using it myself. Consider everything else a gimmick.

It's not meant for pushing out images or even correctly render everything, but you can do so anyway,
provided you read out blend modes, opacity, stencil type attributes and use them with the compositing workflows that PIL provides.
