"""Type hints for TVPy python module by Sas van Gulik @ studio submarine"""

from enum import Enum
from pathlib import Path
from typing import List, Union

import numpy as np
import TVPy

class BlendMode(Enum):
    COLOR = 0
    BEHIND = 1
    ERASE = 2
    SHADE = 3
    LIGHT = 4
    COLORIZE = 5
    TINT = 6
    SATURATE2 = 7
    VALUE = 8
    ADD = 9
    SUB = 10
    MULTIPLY = 11
    SCREEN = 12
    REPLACE = 13
    SUBSTITUTE = 14
    DIFFERENCE = 15
    DIVIDE = 16
    OVERLAY = 17
    OVERLAY2 = 18
    DODGE = 19
    BURN = 20
    HARDLIGHT = 21
    SOFTLIGHT = 22
    GRAINEXTRACT = 23
    GRAINMERGE = 24
    SUBTRACT = 25
    DARKENONLY = 26
    LIGHTENONLY = 27
    ALPHADIFF = 28

class RepeatMode(Enum):
    NONE = 0
    REPEAT = 1
    PINGPONG = 2
    HOLD = 3

class TvpFile:
    """Main wrapper for file information"""
    def __init__(self, path: Union[str, Path]):
        """Construct the file from a valid path on disk, pointing to a *.tvpp file."""
        ...
    @property
    def info(self) -> "TvpFileInfo":
        """Get File information."""
        ...

    @property
    def clips(self) -> List["TvpClip"]:
        """Retrieve a list of all Clips in this file."""
        ...

    def __repr__(self) -> str:
        """Represent the file."""
        ...

    def __getitem__(self, index: int) -> "TvpClip":
        """Retrieve a Clip with an index"""
        ...

    def close(self) -> None:
        """Close file properly and deinitialize memory mapping."""
        ...

    def __enter__(self) -> "TvpFile":
        """Context manager"""
        ...

    def __exit__(self, type, value, traceback) -> None:
        """Exit cleanly."""
        ...

class TvpFileInfo:
    """Container class for all relevant file metadata."""
    @property
    def width(self) -> int:
        """Read only attribute: width"""
        ...

    @property
    def height(self) -> int:
        """Read only attribute: height"""
        ...

    @property
    def fps(self) -> float:
        """Read only attribute: fps"""
        ...

    @property
    def pix_aspect_ratio(self) -> float:
        """Read only attribute: pix_aspect_ratio"""
        ...

    @property
    def field_order(self) -> bool:
        """Read only attribute: field_order"""
        ...

    @property
    def start_frame(self) -> int:
        """Read only attribute: start_frame"""
        ...

    @property
    def uid(self) -> str:
        """Read only attribute: uid"""
        ...

    @property
    def shots(self) -> int:
        """Read only attribute: shots"""
        ...

    @property
    def drawings(self) -> int:
        """Read only attribute: drawings"""
        ...

    @property
    def info(self) -> str:
        """Read only attribute: info"""
        ...

    @property
    def notes(self) -> List[str]:
        """Read only attribute: notes"""
        ...

    @property
    def author(self) -> str:
        """Read only attribute: author"""
        ...

    @property
    def build(self) -> str:
        """Read only attribute: build"""
        ...

    @property
    def host(self) -> str:
        """Read only attribute: host"""
        ...

    @property
    def os(self) -> str:
        """Read only attribute: os"""
        ...

    @property
    def date_creation(self) -> str:
        """Read only attribute: date_creation"""
        ...

    @property
    def date_lastchanged(self) -> str:
        """Read only attribute: date_lastchanged"""
        ...

    @property
    def camera_width(self) -> int:
        """Read only attribute: camera_width"""
        ...

    @property
    def camera_height(self) -> int:
        """Read only attribute: camera_height"""
        ...

    @property
    def camera_field_order(self) -> bool:
        """Read only attribute: camera_field_order"""
        ...

    @property
    def camera_fps(self) -> float:
        """Read only attribute: camera_fps"""
        ...

    @property
    def camera_pix_aspect_ratio(self) -> float:
        """Read only attribute: camera_pix_aspect_ratio"""
        ...

    @property
    def camera_aa(self) -> bool:
        """Read only attribute: camera_aa"""
        ...

    @property
    def camera_show43_border(self) -> bool:
        """Read only attribute: camera_show43_border"""
        ...

    @property
    def camera_safearea(self) -> bool:
        """Read only attribute: camera_safearea"""
        ...

    @property
    def camera_safearea_borderout(self) -> float:
        """Read only attribute: camera_safearea_borderout"""
        ...

    @property
    def camera_safearea_borderin(self) -> float:
        """Read only attribute: camera_safearea_borderin"""
        ...

    @property
    def is_locked(self) -> bool:
        """Read only attribute: is_locked"""
        ...

    @property
    def is_protected(self) -> bool:
        """Read only attribute: is_protected"""
        ...

    @property
    def password(self) -> str:
        """Read only attribute: password"""
        ...

    @property
    def save_audio_deps(self) -> bool:
        """Read only attribute: save_audio_deps"""
        ...

    @property
    def save_video_deps(self) -> bool:
        """Read only attribute: save_video_deps"""
        ...

    @property
    def save_history(self) -> List[str]:
        """Read only attribute: save_history"""
        ...

    @property
    def user_workduration(self) -> float:
        """Read only attribute: user_workduration"""
        ...

    @property
    def user_workchange(self) -> int:
        """Read only attribute: user_workchange"""
        ...

    def __str__(self) -> str:
        """File info, stringified"""
        ...

    def __repr__(self, *args) -> str:
        """Represent TvpFileInfo"""
        ...

class TvpClip:
    """TVPaint Clip Wrapper. Clips hold Layers."""
    @property
    def name(self) -> str:
        """Read only attribute: name"""
        ...

    @property
    def dialog(self) -> str:
        """Read only attribute: dialog"""
        ...

    @property
    def action(self) -> str:
        """Read only attribute: action"""
        ...

    @property
    def note(self) -> str:
        """Read only attribute: note"""
        ...

    @property
    def mark_in(self) -> bool:
        """Read only attribute: mark_in"""
        ...

    @property
    def mark_in_pos(self) -> int:
        """Read only attribute: mark_in_pos"""
        ...

    @property
    def mark_out(self) -> bool:
        """Read only attribute: mark_out"""
        ...

    @property
    def mark_out_pos(self) -> int:
        """Read only attribute: mark_out_pos"""
        ...

    @property
    def hidden(self) -> bool:
        """Read only attribute: hidden"""
        ...

    @property
    def color_idx(self) -> int:
        """Read only attribute: color_idx"""
        ...

    @property
    def layers(self) -> List["TvpLayer"]:
        """Read only: list of stored layers"""
        ...

    def __getitem__(self, index: int) -> "TvpLayer":
        """Grab one layer."""
        ...

    def __str__(self) -> str:
        """Clip info, stringified"""
        ...

    def __repr__(self) -> str: ...

class TvpLayer:
    """TVPaint Layer Wrapper. Layers hold frames, that need to be cached before retrieval."""
    @property
    def name(self) -> str:
        """Read only attribute: name"""
        ...

    @property
    def name_ascii(self) -> str:
        """Read only attribute: name_ascii"""
        ...

    @property
    def first_frame_num(self) -> int:
        """Read only attribute: first_frame_num"""
        ...

    @property
    def frame_offset(self) -> int:
        """Read only attribute: frame_offset"""
        ...

    @property
    def frames_amount(self) -> int:
        """Read only attribute: frames_amount"""
        ...

    @property
    def blend_mode(self) -> TVPy.BlendMode:
        """Read only attribute: blend_mode"""
        ...

    @property
    def repeat_in_type(self) -> TVPy.RepeatMode:
        """Read only attribute: repeat_in_type"""
        ...

    @property
    def repeat_out_type(self) -> TVPy.RepeatMode:
        """Read only attribute: repeat_out_type"""
        ...

    @property
    def group_id(self) -> int:
        """Read only attribute: group_id"""
        ...

    @property
    def opacity(self) -> float:
        """Read only attribute: opacity"""
        ...

    @property
    def invisible(self) -> bool:
        """Read only attribute: invisible"""
        ...

    @property
    def lighttable(self) -> bool:
        """Read only attribute: lighttable"""
        ...

    @property
    def stencil(self) -> bool:
        """Read only attribute: stencil"""
        ...

    @property
    def locked(self) -> bool:
        """Read only attribute: locked"""
        ...

    @property
    def position_locked(self) -> bool:
        """Read only attribute: position_locked"""
        ...

    @property
    def preserve_trans(self) -> bool:
        """Read only attribute: preserve_trans"""
        ...

    def cache_layer(self) -> "TvpLayer":
        """Cache Layer contents."""
        ...

    def release_layer(self) -> "TvpLayer":
        """Release Layer contents."""
        ...

    def get_frame(self, frame: int) -> np.ndarray:
        """Get buffer at specified frame as a uint8 numpy ndarray."""
        ...

    def __str__(self) -> str:
        """Layer info, stringified."""
        ...

    def __getitem__(self, index: int) -> np.ndarray:
        """Get buffer at specified frame as a uint8 numpy ndarray."""
        ...

    def __enter__(self) -> "TvpLayer":
        """On with statement, cache layer contents."""
        ...

    def __exit__(self, type, value, traceback) -> None:
        """Exit cleanly, cleaning up cache."""
        ...
