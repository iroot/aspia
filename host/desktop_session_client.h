//
// PROJECT:         Aspia Remote Desktop
// FILE:            host/desktop_session_client.h
// LICENSE:         See top-level directory
// PROGRAMMERS:     Dmitry Chapyshev (dmitry@aspia.ru)
//

#ifndef _ASPIA_HOST__DESKTOP_SESSION_CLIENT_H
#define _ASPIA_HOST__DESKTOP_SESSION_CLIENT_H

#include "codec/video_encoder.h"
#include "codec/cursor_encoder.h"
#include "host/input_injector.h"
#include "host/screen_updater.h"
#include "host/clipboard_thread.h"
#include "ipc/pipe_channel.h"
#include "proto/desktop_session.pb.h"

namespace aspia {

class DesktopSessionClient :
    private PipeChannel::Delegate,
    private ScreenUpdater::Delegate
{
public:
    DesktopSessionClient();
    ~DesktopSessionClient() = default;

    void Run(const std::wstring& input_channel_name,
             const std::wstring& output_channel_name);

private:
    // Pipe channel implementation.
    void OnPipeChannelConnect(ProcessId peer_pid) override;
    void OnPipeChannelDisconnect() override;
    void OnPipeChannelMessage(const IOBuffer* buffer) override;

    // Screen updater implementation.
    void OnScreenUpdate(const DesktopFrame* screen_frame) override;
    void OnCursorUpdate(std::unique_ptr<MouseCursor> mouse_cursor) override;
    void OnScreenUpdateError() override;

    void WriteMessage(const proto::desktop::HostToClient& message);

    void ReadPointerEvent(const proto::PointerEvent& event);
    void ReadKeyEvent(const proto::KeyEvent& event);
    void ReadClipboardEvent(std::shared_ptr<proto::ClipboardEvent> clipboard_event);
    void ReadPowerEvent(const proto::PowerEvent& event);
    bool ReadConfig(const proto::DesktopConfig& config);

    void SendClipboardEvent(std::unique_ptr<proto::ClipboardEvent> clipboard_event);
    void SendConfigRequest();

private:
    std::unique_ptr<PipeChannel> ipc_channel_;
    std::mutex outgoing_lock_;

    std::unique_ptr<VideoEncoder> video_encoder_;
    std::unique_ptr<CursorEncoder> cursor_encoder_;
    std::unique_ptr<ScreenUpdater> screen_updater_;
    std::unique_ptr<InputInjector> input_injector_;
    std::unique_ptr<ClipboardThread> clipboard_thread_;

    DISALLOW_COPY_AND_ASSIGN(DesktopSessionClient);
};

} // namespace aspia

#endif // _ASPIA_HOST__DESKTOP_SESSION_CLIENT_H