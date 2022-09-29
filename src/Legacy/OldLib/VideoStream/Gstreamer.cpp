#include "Gstreamer.hpp"
#include "gst/gst.h"
#include <gst/app/gstappsink.h>
#include <iostream>

Gstreamer::Gstreamer() :
        src(gst_element_factory_make("udpsrc", "src")),
        gdpdepay(gst_element_factory_make("gdpdepay", "gdp")),
        rtp(gst_element_factory_make("rtph264depay", "rtp")),
        h264parse(gst_element_factory_make("h264parse", "h264parse")),
        decode(gst_element_factory_make("d3d11h264dec", "decode")),
        videoconvert(gst_element_factory_make("autovideoconvert", "videoconvert")),
        sink(gst_element_factory_make("appsink", "sink")),
        group(gst_pipeline_new("group")),
        qImageMutex_(){}

Gstreamer::~Gstreamer() {
    gst_element_set_state(group, GST_STATE_NULL);
    gst_object_unref(group);
}

Gstreamer::operator bool() {
    return src && gdpdepay && rtp && h264parse && decode && videoconvert && sink && group;
}

void Gstreamer::Setup() {
    auto caps = gst_caps_new_simple("video/x-raw",
                                    "format", G_TYPE_STRING, "RGB",
                                    "width", G_TYPE_INT, 1920,
                                    "height", G_TYPE_INT, 1080,
                                    "framerate", GST_TYPE_FRACTION, 0, 1,
                                    nullptr);

    g_object_set(src, "port", 8000, nullptr);

    gst_bin_add_many(GST_BIN (group), src, gdpdepay, rtp, h264parse, decode, videoconvert, sink, nullptr);

    gst_element_link_filtered(videoconvert, sink, caps);

    gst_caps_unref(caps);

    gst_element_link_many(src, gdpdepay, rtp, h264parse, decode, videoconvert, sink, nullptr);
}

QImage Gstreamer::GetFrame() {
    QImage img;

    auto ms = [](uint64_t ms) constexpr { return ms * 1000 * 1000; };
        auto sample = gst_app_sink_try_pull_sample (GST_APP_SINK(sink), ms(500));

    if (sample) {
        GstMapInfo buffInfo;
        auto buffer = gst_sample_get_buffer(sample);
        if(!buffer)
            return img;

        gst_buffer_map(buffer, &buffInfo, GST_MAP_READ);

        auto frameBufferPtr = reinterpret_cast<const uchar *>(buffInfo.data);

        img = QImage(frameBufferPtr, 1920, 1080, QImage::Format_RGB888);

        gst_buffer_unmap(buffer, &buffInfo);
        gst_sample_unref(sample);
    }

    return img;
}

bool Gstreamer::SetStatePlaying() {
    return gst_element_set_state(group, GST_STATE_PLAYING);
}

///************Init Gstreamer*************
extern "C" void InitGstreamer() {

    gst_init(nullptr, nullptr);

    GST_PLUGIN_STATIC_DECLARE(coreelements);
    GST_PLUGIN_STATIC_REGISTER(coreelements);

    GST_PLUGIN_STATIC_DECLARE(udp);
    GST_PLUGIN_STATIC_REGISTER(udp);

    GST_PLUGIN_STATIC_DECLARE(gdp);
    GST_PLUGIN_STATIC_REGISTER(gdp);

    GST_PLUGIN_STATIC_DECLARE(rtp);
    GST_PLUGIN_STATIC_REGISTER(rtp);

    GST_PLUGIN_STATIC_DECLARE(playback);
    GST_PLUGIN_STATIC_REGISTER(playback);

    GST_PLUGIN_STATIC_DECLARE(autoconvert);
    GST_PLUGIN_STATIC_REGISTER(autoconvert);

    GST_PLUGIN_STATIC_DECLARE(app);
    GST_PLUGIN_STATIC_REGISTER(app);

    /*delete*/
    GST_PLUGIN_STATIC_DECLARE(videotestsrc);
    GST_PLUGIN_STATIC_REGISTER(videotestsrc);

    GST_PLUGIN_STATIC_DECLARE(d3d11);
    GST_PLUGIN_STATIC_REGISTER(d3d11);

    GST_PLUGIN_STATIC_DECLARE(videoparsersbad);
    GST_PLUGIN_STATIC_REGISTER(videoparsersbad);

    GST_PLUGIN_STATIC_DECLARE(autodetect);
    GST_PLUGIN_STATIC_REGISTER(autodetect);

    GST_PLUGIN_STATIC_DECLARE(videoconvert);
    GST_PLUGIN_STATIC_REGISTER(videoconvert);
}