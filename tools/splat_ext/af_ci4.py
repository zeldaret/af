import n64img.image

from .af_ci import N64SegAf_ci


class N64SegAf_ci4(N64SegAf_ci):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs, img_cls=n64img.image.CI4)
