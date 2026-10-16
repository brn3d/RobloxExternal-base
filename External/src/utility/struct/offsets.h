#pragma once

#include <cstdint>
#include <string>
namespace Offsets {
    inline std::string ClientVersion = "version-11f155f3450f4c8e";

    namespace AirProperties {
         inline constexpr uintptr_t AirDensity = 0x18;
         inline constexpr uintptr_t GlobalWind = 0x3c;
    }

    namespace AnimationTrack {
         inline constexpr uintptr_t Animation = 0xa8;
         inline constexpr uintptr_t Animator = 0x100;
         inline constexpr uintptr_t IsPlaying = 0xa48;
         inline constexpr uintptr_t Looped = 0xd4;
         inline constexpr uintptr_t Speed = 0xc4;
         inline constexpr uintptr_t TimePosition = 0xc8;
    }

    namespace Animator {
         inline constexpr uintptr_t ActiveAnimations = 0xa80;
    }

    namespace Atmosphere {
         inline constexpr uintptr_t Color = 0xa8;
         inline constexpr uintptr_t Decay = 0xb4;
         inline constexpr uintptr_t Density = 0xc0;
         inline constexpr uintptr_t Glare = 0xc4;
         inline constexpr uintptr_t Haze = 0xc8;
         inline constexpr uintptr_t Offset = 0xcc;
    }

    namespace Attachment {
         inline constexpr uintptr_t Position = 0xb4;
    }

    namespace BasePart {
         inline constexpr uintptr_t CastShadow = 0x128;
         inline constexpr uintptr_t Color3 = 0x1ac;
         inline constexpr uintptr_t Locked = 0x129;
         inline constexpr uintptr_t Massless = 0x12a;
         inline constexpr uintptr_t Primitive = 0x180;
         inline constexpr uintptr_t Reflectance = 0xfc;
         inline constexpr uintptr_t Shape = 0x1a8;
         inline constexpr uintptr_t Transparency = 0x120;
    }

    namespace Beam {
         inline constexpr uintptr_t Attachment0 = 0x150;
         inline constexpr uintptr_t Attachment1 = 0x160;
         inline constexpr uintptr_t Brightness = 0x170;
         inline constexpr uintptr_t CurveSize0 = 0x174;
         inline constexpr uintptr_t CurveSize1 = 0x178;
         inline constexpr uintptr_t LightEmission = 0x17c;
         inline constexpr uintptr_t LightInfluence = 0x180;
         inline constexpr uintptr_t Texture = 0x130;
         inline constexpr uintptr_t TextureLength = 0x18c;
         inline constexpr uintptr_t TextureSpeed = 0x194;
         inline constexpr uintptr_t Width0 = 0x198;
         inline constexpr uintptr_t Width1 = 0x19c;
         inline constexpr uintptr_t ZOffset = 0x1a0;
    }

    namespace BloomEffect {
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t Intensity = 0xa8;
         inline constexpr uintptr_t Size = 0xac;
         inline constexpr uintptr_t Threshold = 0xb0;
    }

    namespace BlurEffect {
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t Size = 0xa8;
    }

    namespace BoundFuncDescriptor {
         inline constexpr uintptr_t Function = 0x90;
         inline constexpr uintptr_t Name = 0x8;
    }

    namespace Btools {
         inline constexpr uintptr_t MouseCommandWorkspace = 0x50;
         inline constexpr uintptr_t ToolAllocationSize = 0x100;
         inline constexpr uintptr_t WorkspaceCurrentCommand = 0x878;
         inline constexpr uintptr_t WorkspaceStickyCommand = 0x880;
    }

    namespace ByteCode {
         inline constexpr uintptr_t Pointer = 0x18;
         inline constexpr uintptr_t Size = 0x28;
    }

    namespace Bytecode {
         inline constexpr uintptr_t BytecodeVerificationTableA = 0xd22f50;
         inline constexpr uintptr_t LuaVMLoad = 0x41a3610;
    }

    namespace CachedItem {
         inline constexpr uintptr_t FileMeshData = 0x40;
    }

    namespace Camera {
         inline constexpr uintptr_t CFrame = 0xc8;
         inline constexpr uintptr_t CameraSubject = 0xb8;
         inline constexpr uintptr_t CameraType = 0x28f;
         inline constexpr uintptr_t FieldOfView = 0x130;
         inline constexpr uintptr_t ImagePlaneDepth = 0x2d4;
         inline constexpr uintptr_t Position = 0xec;
         inline constexpr uintptr_t Rotation = 0xc8;
         inline constexpr uintptr_t Viewport = 0x28c;
         inline constexpr uintptr_t ViewportSize = 0x2cc;
    }

    namespace CharacterMesh {
         inline constexpr uintptr_t BaseTextureId = 0xb8;
         inline constexpr uintptr_t BodyPart = 0x138;
         inline constexpr uintptr_t MeshId = 0xe8;
         inline constexpr uintptr_t OverlayTextureId = 0x118;
    }

    namespace ClassDescriptor {
         inline constexpr uintptr_t ClassName = 0x8;
         inline constexpr uintptr_t EventDescriptors = 0x88;
         inline constexpr uintptr_t FunctionDescriptors = 0xd0;
         inline constexpr uintptr_t PropertyDescriptors = 0x40;
    }

    namespace ClickDetector {
         inline constexpr uintptr_t MaxActivationDistance = 0xd8;
         inline constexpr uintptr_t MouseIcon = 0xb8;
    }

    namespace ClientBuild {
         inline constexpr uintptr_t EntityDrawRva = 0x399f220;
         inline constexpr uintptr_t EntitySubmitRva = 0x399f770;
         inline constexpr uintptr_t ImageSize = 0x9318000;
         inline constexpr uintptr_t MergeFlag = 0x888c668;
         inline constexpr uintptr_t Timestamp = 0xfd803185;
    }

    namespace Clothing {
         inline constexpr uintptr_t Color3 = 0x110;
         inline constexpr uintptr_t Template = 0xf0;
    }

    namespace ColorCorrectionEffect {
         inline constexpr uintptr_t Brightness = 0xb4;
         inline constexpr uintptr_t Contrast = 0xb8;
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t TintColor = 0xa8;
    }

    namespace ColorGradingEffect {
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t TonemapperPreset = 0xa8;
    }

    namespace Coroutine {
         inline constexpr uintptr_t create = 0x5904ca0;
         inline constexpr uintptr_t finally = 0x5906bf0;
         inline constexpr uintptr_t isyieldable = 0x59055a0;
         inline constexpr uintptr_t running = 0x5905530;
         inline constexpr uintptr_t status = 0x5903230;
         inline constexpr uintptr_t wrap = 0x5905260;
         inline constexpr uintptr_t yield = 0x59054d0;
    }

    namespace DataModel {
         inline constexpr uintptr_t CreatorId = 0x178;
         inline constexpr uintptr_t GameId = 0x180;
         inline constexpr uintptr_t GameLoaded = 0x5d0;
         inline constexpr uintptr_t JobId = 0x110;
         inline constexpr uintptr_t PlaceId = 0x188;
         inline constexpr uintptr_t PlaceVersion = 0x1a4;
         inline constexpr uintptr_t PrimitiveCount = 0x418;
         inline constexpr uintptr_t ScriptContext = 0x440;
         inline constexpr uintptr_t ServerIP = 0x5b8;
         inline constexpr uintptr_t ToRenderView1 = 0x1c0;
         inline constexpr uintptr_t ToRenderView2 = 0x8;
         inline constexpr uintptr_t ToRenderView3 = 0x28;
         inline constexpr uintptr_t Workspace = 0x150;
    }

    namespace DepthOfFieldEffect {
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t FarIntensity = 0xa8;
         inline constexpr uintptr_t FocusDistance = 0xac;
         inline constexpr uintptr_t InFocusRadius = 0xb0;
         inline constexpr uintptr_t NearIntensity = 0xb4;
    }

    namespace Descriptor {
         inline constexpr uintptr_t Name = 0x8;
    }

    namespace DeviceD3D11Gfx {
         inline constexpr uintptr_t Context = 0x178;
         inline constexpr uintptr_t ContextObj = 0x1b0;
         inline constexpr uintptr_t ContextObjAlt = 0x268;
         inline constexpr uintptr_t ContextObjDrawRva = 0x2812ee0;
         inline constexpr uintptr_t ContextObjDrawSlot = 0x1c;
         inline constexpr uintptr_t ContextObjLegacy = 0x1f8;
         inline constexpr uintptr_t ContextObjLinkScan = 0x570;
         inline constexpr uintptr_t ContextObjToContext = 0x18;
         inline constexpr uintptr_t ContextObjVTableLen = 0x27;
         inline constexpr uintptr_t ContextObjVTableRva = 0x6ec0370;
         inline constexpr uintptr_t ContextPtr = 0x178;
         inline constexpr uintptr_t DevicePtr = 0x178;
         inline constexpr uintptr_t DevicePtrLegacy = 0x228;
         inline constexpr uintptr_t SwapChainPtr = 0x80;
         inline constexpr uintptr_t VTableRva = 0x6ebfef8;
    }

    namespace DragDetector {
         inline constexpr uintptr_t ActivatedCursorIcon = 0x1b0;
         inline constexpr uintptr_t CursorIcon = 0xb8;
         inline constexpr uintptr_t MaxActivationDistance = 0xd8;
         inline constexpr uintptr_t MaxDragAngle = 0x298;
         inline constexpr uintptr_t MaxDragTranslation = 0x25c;
         inline constexpr uintptr_t MaxForce = 0x29c;
         inline constexpr uintptr_t MaxTorque = 0x2a0;
         inline constexpr uintptr_t MinDragAngle = 0x2a4;
         inline constexpr uintptr_t MinDragTranslation = 0x268;
         inline constexpr uintptr_t ReferenceInstance = 0x1e0;
         inline constexpr uintptr_t Responsiveness = 0x2b0;
    }

    namespace EngineWallCheck {
         inline constexpr uintptr_t BoundFnOffset = 0x90;
         inline constexpr uintptr_t KernelVtableRva = 0x70b22d0;
         inline constexpr uintptr_t RaycastDescriptorRva = 0x8557620;
         inline constexpr uintptr_t RaycastWorkerRva = 0x8f6754b;
         inline constexpr uintptr_t RealWrapperRva = 0xd5c500;
         inline constexpr uintptr_t StepWorldRva = 0x72a9d0;
    }

    namespace FFlags {
         inline constexpr uintptr_t EnableLoadModule = 0x8891880;
         inline constexpr uintptr_t GetFFlag = 0x49f8d70;
         inline constexpr uintptr_t NextGenReplicatorEnabledWrite4 = 0x85482f8;
         inline constexpr uintptr_t PhysicsSenderMaxBandwidthBps = 0x8026ca8;
         inline constexpr uintptr_t PhysicsSenderMaxBandwidthBpsScaling = 0x8026cd0;
         inline constexpr uintptr_t RenderFastClusterOcclusionCulling4 = 0x88887d8;
         inline constexpr uintptr_t SetFFlag = 0x49f8270;
    }

    namespace FakeDataModel {
         inline constexpr uintptr_t Pointer = 0x8dc8000;
         inline constexpr uintptr_t RealDataModel = 0x1f8;
    }

    namespace FastCluster {
         inline constexpr uintptr_t ClusterNode = 0x188;
         inline constexpr uintptr_t MeshEntityVTableRva = 0x6f2c1a0;
         inline constexpr uintptr_t VTableRva = 0x6f2ada0;
         inline constexpr uintptr_t VTableRvaAlt = 0x6f2ada0;
         inline constexpr uintptr_t VTableRvaSub = 0x6f2ad80;
         inline constexpr uintptr_t VTableRvaSubAlt = 0x6f2b0b0;
    }

    namespace FastClusterBinding {
         inline constexpr uintptr_t Owner = 0x60;
         inline constexpr uintptr_t Subobject = 0x90;
         inline constexpr uintptr_t VTableRva = 0x6f2c080;
    }

    namespace FastClusterEntity {
         inline constexpr uintptr_t AlphaByte = 0x14;
         inline constexpr uintptr_t BBoxMaxX = 0xa4;
         inline constexpr uintptr_t BBoxMaxY = 0xa8;
         inline constexpr uintptr_t BBoxMaxZ = 0xac;
         inline constexpr uintptr_t BBoxMinX = 0x98;
         inline constexpr uintptr_t BBoxMinY = 0x9c;
         inline constexpr uintptr_t BBoxMinZ = 0xa0;
         inline constexpr uintptr_t CollectedPasses = 0x18;
         inline constexpr uintptr_t ContextPtr = 0x8;
         inline constexpr uintptr_t DecalMaterialPtr = 0x48;
         inline constexpr uintptr_t Highlight = 0xb4;
         inline constexpr uintptr_t MaterialPtr = 0x20;
         inline constexpr uintptr_t PrimitiveIndexArrayPtr = 0x80;
         inline constexpr uintptr_t RenderQueueId = 0x10;
         inline constexpr uintptr_t TechniqueArrayPtr = 0x70;
         inline constexpr uintptr_t VTableRva = 0x6f2c158;
         namespace Context {
              inline constexpr uintptr_t PrimitivePoolPtr = 0x198;
         }
         namespace PrimitivePool {
              inline constexpr uintptr_t ArrayBase = 0x20;
         }
         namespace PrimitiveRecord {
              inline constexpr uintptr_t Row0 = 0;
              inline constexpr uintptr_t Row1 = 12;
              inline constexpr uintptr_t Row2 = 24;
              inline constexpr uintptr_t Stride = 48;
              inline constexpr uintptr_t Translation = 36;
         }
    }

    namespace FileMeshData {
         inline constexpr uintptr_t AABBMax = 0x18c;
         inline constexpr uintptr_t AABBMin = 0x180;
         inline constexpr uintptr_t Faces = 0x30;
         inline constexpr uintptr_t FacesEnd = 0x38;
         inline constexpr uintptr_t VerticesEnd = 0x8;
    }

    namespace Fire {
         inline constexpr uintptr_t FireProximityPrompt = 0x30d1720;
    }

    namespace Frame {
         inline constexpr uintptr_t FramePositionOffsetX = 0x504;
         inline constexpr uintptr_t FramePositionOffsetY = 0x50c;
    }

    namespace FunctionDescriptor {
         inline constexpr uintptr_t Function = 0x80;
    }

    namespace Functions {
         inline constexpr uintptr_t CastArgs = 0x7bff10;
         inline constexpr uintptr_t Clone = 0x433c08b;
         inline constexpr uintptr_t Destroy = 0x18687c0;
         inline constexpr uintptr_t FireServer = 0x39ae800;
         inline constexpr uintptr_t Print = 0x1ce58f0;
         inline constexpr uintptr_t Shapecast = 0x2783244;
         inline constexpr uintptr_t WaitForChild = 0x3b349ed;
    }

    namespace GeometryD3D11 {
         inline constexpr uintptr_t VTableRva = 0x6ec0678;
    }

    inline constexpr uintptr_t ClusterNode = 0x188;

    namespace GuiBase2D {
         inline constexpr uintptr_t AbsolutePosition = 0xfc;
         inline constexpr uintptr_t AbsoluteRotation = 0xd8;
         inline constexpr uintptr_t AbsoluteSize = 0x104;
    }

    namespace GuiObject {
         inline constexpr uintptr_t BackgroundColor3 = 0x530;
         inline constexpr uintptr_t BackgroundTransparency = 0x53c;
         inline constexpr uintptr_t BorderColor3 = 0x53c;
         inline constexpr uintptr_t Image = 0x9a8;
         inline constexpr uintptr_t LayoutOrder = 0x56c;
         inline constexpr uintptr_t Position = 0x500;
         inline constexpr uintptr_t RichText = 0xba0;
         inline constexpr uintptr_t Rotation = 0xd8;
         inline constexpr uintptr_t ScreenGui_Enabled = 0x4b4;
         inline constexpr uintptr_t Size = 0x520;
         inline constexpr uintptr_t Text = 0xe08;
         inline constexpr uintptr_t TextColor3 = 0xeb8;
         inline constexpr uintptr_t Visible = 0x59d;
         inline constexpr uintptr_t ZIndex = 0x594;
    }

    namespace Highlight {
         inline constexpr uintptr_t Adornee = 0xa8;
         inline constexpr uintptr_t DepthMode = 0xd0;
         inline constexpr uintptr_t Enabled = 0xd8;
         inline constexpr uintptr_t FillColor = 0xb8;
         inline constexpr uintptr_t FillTransparency = 0xd4;
         inline constexpr uintptr_t OutlineColor = 0xc4;
         inline constexpr uintptr_t OutlineTransparency = 0xdc;
    }

    namespace HighlightManager {
         inline constexpr uintptr_t ContextActive = 0x420;
         inline constexpr uintptr_t ContextDepth = 0x20;
         inline constexpr uintptr_t ContextFill = 0x520;
         inline constexpr uintptr_t ContextOutline = 0x1520;
         inline constexpr uintptr_t ContextStride = 0x2520;
         inline constexpr uintptr_t Contexts = 0x100;
         inline constexpr uintptr_t FallbackActive = 0x538;
         inline constexpr uintptr_t FallbackDepth = 0x138;
         inline constexpr uintptr_t FallbackFill = 0x638;
         inline constexpr uintptr_t FallbackOutline = 0x1638;
         inline constexpr uintptr_t GlobalActive = 0x2aac;
         inline constexpr uintptr_t GlobalDepth = 0x26ac;
         inline constexpr uintptr_t GlobalFill = 0x2bac;
         inline constexpr uintptr_t GlobalNext = 0x26a8;
         inline constexpr uintptr_t GlobalOutline = 0x3bac;
         inline constexpr uintptr_t Manager = 0xc10;
         inline constexpr uintptr_t MergeFlag = 0x888c668;
    }

    namespace HopperBin {
         inline constexpr std::uint32_t BinType = 1112u;
    }

    namespace Humanoid {
         inline constexpr uintptr_t AutoJumpEnabled = 0x1d0;
         inline constexpr uintptr_t AutoRotate = 0x1d1;
         inline constexpr uintptr_t AutomaticScalingEnabled = 0x1d2;
         inline constexpr uintptr_t BreakJointsOnDeath = 0x1d3;
         inline constexpr uintptr_t CameraOffset = 0x118;
         inline constexpr uintptr_t DisplayDistanceType = 0x17c;
         inline constexpr uintptr_t DisplayName = 0xa8;
         inline constexpr uintptr_t EvaluateStateMachine = 0x1d4;
         inline constexpr uintptr_t FloorMaterial = 0x180;
         inline constexpr uintptr_t Health = 0x18c;
         inline constexpr uintptr_t HealthDisplayDistance = 0x184;
         inline constexpr uintptr_t HealthDisplayType = 0x188;
         inline constexpr uintptr_t HipHeight = 0x190;
         inline constexpr uintptr_t HumanoidRootPart = 0x468;
         inline constexpr uintptr_t HumanoidState = 0x8b0;
         inline constexpr uintptr_t HumanoidStateID = 0x20;
         inline constexpr uintptr_t IsWalking = 0x956;
         inline constexpr uintptr_t Jump = 0x1d7;
         inline constexpr uintptr_t JumpHeight = 0x19c;
         inline constexpr uintptr_t JumpPower = 0x1a0;
         inline constexpr uintptr_t MaxHealth = 0x1a4;
         inline constexpr uintptr_t MaxSlopeAngle = 0x1a8;
         inline constexpr uintptr_t MoveDirection = 0x13c;
         inline constexpr uintptr_t MoveToPoint = 0x160;
         inline constexpr uintptr_t NameDisplayDistance = 0x1ac;
         inline constexpr uintptr_t NameOcclusion = 0x1b0;
         inline constexpr uintptr_t PlatformStand = 0x1d9;
         inline constexpr uintptr_t RequiresNeck = 0x1da;
         inline constexpr uintptr_t RigType = 0x1bc;
         inline constexpr uintptr_t SeatPart = 0xf8;
         inline constexpr uintptr_t Sit = 0x1da;
         inline constexpr uintptr_t TargetPoint = 0x148;
         inline constexpr uintptr_t UseJumpPower = 0x1dd;
         inline constexpr uintptr_t Walkspeed = 0x1cc;
         inline constexpr uintptr_t WalkspeedCheck = 0x3a4;
    }

    namespace Instance {
         inline constexpr uintptr_t ChildrenEnd = 0x8;
         inline constexpr uintptr_t ChildrenStart = 0x78;
         inline constexpr uintptr_t ClassBase = 0x1b0;
         inline constexpr uintptr_t ClassDescriptor = 0x18;
         inline constexpr uintptr_t FindFirstAncestorWhichIsA = 0x20ac120;
         inline constexpr uintptr_t FindFirstChild = 0xb2c868;
         inline constexpr uintptr_t FindFirstChildOfClass = 0xb2c868;
         inline constexpr uintptr_t GetAttribute = 0x23794;
         inline constexpr uintptr_t GetChildren = 0x22ac8d0;
         inline constexpr uintptr_t Index = 0x412b7d0;
         inline constexpr uintptr_t Name = 0x8;
         inline constexpr uintptr_t NameContainer = 0x70;
         inline constexpr uintptr_t New = 0x42c96a0;
         inline constexpr uintptr_t Parent = 0x68;
         inline constexpr uintptr_t This = 0x8;
    }

    namespace LRUHolder {
         inline constexpr uintptr_t MemEnforcedLRUCache = 0x20;
    }

    namespace LRUNode {
         inline constexpr uintptr_t AssetID = 0x10;
         inline constexpr uintptr_t CachedItem = 0x40;
         inline constexpr uintptr_t Next = 0x0;
    }

    namespace Lighting {
         inline constexpr uintptr_t Ambient = 0xc0;
         inline constexpr uintptr_t Brightness = 0x108;
         inline constexpr uintptr_t ClockTime = 0xb8;
         inline constexpr uintptr_t ColorShift_Bottom = 0xd8;
         inline constexpr uintptr_t ColorShift_Top = 0xcc;
         inline constexpr uintptr_t EnvironmentDiffuseScale = 0x10c;
         inline constexpr uintptr_t EnvironmentSpecularScale = 0x110;
         inline constexpr uintptr_t ExposureCompensation = 0x114;
         inline constexpr uintptr_t FogColor = 0x14c;
         inline constexpr uintptr_t FogEnd = 0x11c;
         inline constexpr uintptr_t FogStart = 0x120;
         inline constexpr uintptr_t GeographicLatitude = 0x124;
         inline constexpr uintptr_t GlobalShadows = 0x134;
         inline constexpr uintptr_t GradientBottom = 0x180;
         inline constexpr uintptr_t GradientTop = 0x140;
         inline constexpr uintptr_t LightColor = 0x14c;
         inline constexpr uintptr_t LightDirection = 0x158;
         inline constexpr uintptr_t MoonPosition = 0x174;
         inline constexpr uintptr_t OutdoorAmbient = 0xf0;
         inline constexpr uintptr_t Sky = 0x1b8;
         inline constexpr uintptr_t Source = 0x164;
         inline constexpr uintptr_t SunPosition = 0x168;
    }

    namespace LocalScript {
         inline constexpr uintptr_t ByteCode = 0x180;
         inline constexpr uintptr_t GUID = 0xc0;
         inline constexpr uintptr_t Hash = 0x190;
    }

    namespace Luau {
         inline constexpr uintptr_t Capability = 0x26585a0;
         inline constexpr uintptr_t GetGlobalState = 0x41acdb0;
         inline constexpr uintptr_t LuaVMLoad = 0x9f6d00;
         inline constexpr uintptr_t dumpgco = 0x265b350;
         inline constexpr uintptr_t ktable = 0x411b7d0;
         inline constexpr uintptr_t luaB_assert = 0x2682c50;
         inline constexpr uintptr_t luaB_error = 0x267b730;
         inline constexpr uintptr_t luaB_gcinfo = 0x2681590;
         inline constexpr uintptr_t luaB_getfenv = 0x267cce0;
         inline constexpr uintptr_t luaB_getmetatable = 0x267c170;
         inline constexpr uintptr_t luaB_newproxy = 0x2683b70;
         inline constexpr uintptr_t luaB_next = 0x26821a0;
         inline constexpr uintptr_t luaB_print = 0x267b2d0;
         inline constexpr uintptr_t luaB_rawequal = 0x267cfd0;
         inline constexpr uintptr_t luaB_rawget = 0x267d0e0;
         inline constexpr uintptr_t luaB_rawlen = 0x26814f0;
         inline constexpr uintptr_t luaB_rawset = 0x267df50;
         inline constexpr uintptr_t luaB_select = 0x2682d00;
         inline constexpr uintptr_t luaB_setfenv = 0x267cda0;
         inline constexpr uintptr_t luaB_setmetatable = 0x267c300;
         inline constexpr uintptr_t luaB_tonumber = 0x267b3a0;
         inline constexpr uintptr_t luaB_tostring = 0x2683b10;
         inline constexpr uintptr_t luaB_type = 0x26815b0;
         inline constexpr uintptr_t luaB_typeof = 0x2681bb0;
         inline constexpr uintptr_t luaC_init = 0x265de50;
         inline constexpr uintptr_t luaC_step = 0x2644300;
         inline constexpr uintptr_t luaD_Throw = 0x262ddc0;
         inline constexpr uintptr_t luaF_FreeProto = 0xd195a0;
         inline constexpr uintptr_t luaG_runerror = 0x7bf930;
         inline constexpr uintptr_t luaH_clone = 0x2694180;
         inline constexpr uintptr_t luaH_dummynode = 0x2619a00;
         inline constexpr uintptr_t luaL_argerror = 0x2623300;
         inline constexpr uintptr_t luaL_checktype = 0x2622820;
         inline constexpr uintptr_t luaM_newgco = 0x265dce0;
         inline constexpr uintptr_t luaM_visitgco = 0x66992cb;
         inline constexpr uintptr_t luaO_nilobject = 0x26199c8;
         inline constexpr uintptr_t luaO_pushfstring = 0x2657710;
         inline constexpr uintptr_t lua_checkstack = 0xcb8d00;
         inline constexpr uintptr_t lua_error = 0x261d640;
         inline constexpr uintptr_t lua_newstate = 0x26210c0;
         inline constexpr uintptr_t lua_pushfstring = 0x261ad70;
         inline constexpr uintptr_t luau_execute = 0x266c81c;
         inline constexpr uintptr_t print = 0x1ce58f0;
         inline constexpr uintptr_t pseudo2addr = 0x2619930;
         inline constexpr uintptr_t tclone = 0x2693f30;
    }

    namespace Luau::global_State {
         inline constexpr uintptr_t g_gcstepmul = 0x30;
    }

    namespace Luau::lua_State {
         inline constexpr uintptr_t L_global_offset = 0x50;
    }

    namespace MaterialColors {
         inline constexpr uintptr_t Asphalt = 0x30;
         inline constexpr uintptr_t Basalt = 0x27;
         inline constexpr uintptr_t Brick = 0xf;
         inline constexpr uintptr_t Cobblestone = 0x33;
         inline constexpr uintptr_t Concrete = 0xc;
         inline constexpr uintptr_t CrackedLava = 0x2d;
         inline constexpr uintptr_t Glacier = 0x1b;
         inline constexpr uintptr_t Grass = 0x6;
         inline constexpr uintptr_t Ground = 0x2a;
         inline constexpr uintptr_t Ice = 0x36;
         inline constexpr uintptr_t LeafyGrass = 0x39;
         inline constexpr uintptr_t Limestone = 0x3f;
         inline constexpr uintptr_t Mud = 0x24;
         inline constexpr uintptr_t Pavement = 0x42;
         inline constexpr uintptr_t Rock = 0x18;
         inline constexpr uintptr_t Salt = 0x3c;
         inline constexpr uintptr_t Sand = 0x12;
         inline constexpr uintptr_t Sandstone = 0x21;
         inline constexpr uintptr_t Slate = 0x9;
         inline constexpr uintptr_t Snow = 0x1e;
         inline constexpr uintptr_t WoodPlanks = 0x15;
    }

    namespace MaterialLayer {
         inline constexpr uintptr_t ColorData = 0x26;
         inline constexpr uintptr_t CullMode = 0x10;
         inline constexpr uintptr_t FillModeByte = 0x11;
         inline constexpr uintptr_t Flags2 = 0x20;
         inline constexpr uintptr_t MatFlags = 0x18;
         inline constexpr uintptr_t Param = 0x1c;
         inline constexpr uintptr_t Stride = 0x88;
    }

    namespace MemEnforcedLRUCache {
         inline constexpr uintptr_t Head = 0x8;
    }

    namespace MeshContentProvider {
         inline constexpr uintptr_t LRUHolder = 0xc8;
    }

    namespace MeshPart {
         inline constexpr uintptr_t MeshId = 0x300;
         inline constexpr uintptr_t Texture = 0x330;
    }

    namespace Misc {
         inline constexpr uintptr_t Adornee = 0xe0;
         inline constexpr uintptr_t AnimationId = 0xb0;
         inline constexpr uintptr_t PrintIdentity = 0x425f710;
         inline constexpr uintptr_t RequireBypass = 0xa81;
         inline constexpr uintptr_t StringLength = 0x10;
         inline constexpr uintptr_t Value = 0xa8;
    }

    namespace Model {
         inline constexpr uintptr_t PrimaryPart = 0x248;
         inline constexpr uintptr_t Scale = 0x134;
    }

    namespace ModuleScript {
         inline constexpr uintptr_t ByteCode = 0x128;
         inline constexpr uintptr_t GUID = 0xc0;
         inline constexpr uintptr_t Hash = 0x190;
         inline constexpr uintptr_t HashLookUp = 0x72657a0;
         inline constexpr uintptr_t IsCoreScript = 0x158;
         inline constexpr uintptr_t IsRobloxScript = 0x9a;
    }

    namespace Motor6D {
         inline constexpr uintptr_t ChildName = 0x118;
         inline constexpr uintptr_t ParentName = 0x108;
    }

    namespace Mouse {
         inline constexpr uintptr_t FireProximityPrompt = 0x30d1720;
    }

    namespace MouseService {
         inline constexpr uintptr_t InputObject = 0xe0;
         inline constexpr uintptr_t InputObject2 = 0xf0;
         inline constexpr uintptr_t MousePosition = 0xc4;
    }

    namespace ParticleEmitter {
         inline constexpr uintptr_t Acceleration = 0x1d0;
         inline constexpr uintptr_t Brightness = 0x20c;
         inline constexpr uintptr_t Drag = 0x210;
         inline constexpr uintptr_t Lifetime = 0x1e4;
         inline constexpr uintptr_t LightEmission = 0x228;
         inline constexpr uintptr_t LightInfluence = 0x22c;
         inline constexpr uintptr_t Rate = 0x238;
         inline constexpr uintptr_t RotSpeed = 0x1ec;
         inline constexpr uintptr_t Rotation = 0x1f4;
         inline constexpr uintptr_t Speed = 0x1fc;
         inline constexpr uintptr_t SpreadAngle = 0x204;
         inline constexpr uintptr_t Texture = 0x1b0;
         inline constexpr uintptr_t TimeScale = 0x24c;
         inline constexpr uintptr_t VelocityInheritance = 0x250;
         inline constexpr uintptr_t ZOffset = 0x254;
    }

    namespace Player {
         inline constexpr uintptr_t AccountAge = 0x35c;
         inline constexpr uintptr_t CameraMode = 0x370;
         inline constexpr uintptr_t DisplayName = 0x128;
         inline constexpr uintptr_t HealthDisplayDistance = 0x394;
         inline constexpr uintptr_t LocalPlayer = 0x120;
         inline constexpr uintptr_t LocaleId = 0x788;
         inline constexpr uintptr_t MaxZoomDistance = 0x368;
         inline constexpr uintptr_t MinZoomDistance = 0x36c;
         inline constexpr uintptr_t ModelInstance = 0x298;
         inline constexpr uintptr_t NameDisplayDistance = 0x3a4;
         inline constexpr uintptr_t Team = 0x2d8;
         inline constexpr uintptr_t TeamColor = 0x3b0;
         inline constexpr uintptr_t UserId = 0xc0;
    }

    namespace Primitive {
         inline constexpr uintptr_t AssemblyAngularVelocity = 0xec;
         inline constexpr uintptr_t AssemblyLinearVelocity = 0xe0;
         inline constexpr uintptr_t Flags = 0x1be;
         inline constexpr uintptr_t Material = 0x24e;
         inline constexpr uintptr_t Owner = 0x218;
         inline constexpr uintptr_t Position = 0xd4;
         inline constexpr uintptr_t Rotation = 0xb0;
         inline constexpr uintptr_t Size = 0x1c4;
         inline constexpr uintptr_t Validate = 0x6;
    }

    namespace PrimitiveFlags {
         inline constexpr uintptr_t Anchored = 0x2;
         inline constexpr uintptr_t CanCollide = 0x8;
         inline constexpr uintptr_t CanQuery = 0x20;
         inline constexpr uintptr_t CanTouch = 0x10;
    }

    namespace Property {
         inline constexpr uintptr_t GetPropertyData = 0x7c47e0;
    }

    namespace PropertyDescriptor {
         inline constexpr uintptr_t GetSetImpl = 0x98;
         inline constexpr uintptr_t TType = 0x70;
    }

    namespace ProximityPrompt {
         inline constexpr uintptr_t ActionText = 0xa0;
         inline constexpr uintptr_t Enabled = 0x126;
         inline constexpr uintptr_t GamepadKeyCode = 0x10c;
         inline constexpr uintptr_t HoldDuration = 0x110;
         inline constexpr uintptr_t KeyCode = 0x114;
         inline constexpr uintptr_t MaxActivationDistance = 0x118;
         inline constexpr uintptr_t ObjectText = 0xc0;
         inline constexpr uintptr_t RequiresLineOfSight = 0x127;
    }

    namespace RakNet {
         inline constexpr uintptr_t RakNetReliabilityLayerSend = 0xba0160;
         inline constexpr uintptr_t RakNetSend = 0x2852d00;
         inline constexpr uintptr_t RakPeerProcessNetworkPacket = 0x28532c0;
         inline constexpr uintptr_t RakPeerReceive = 0x848900;
         inline constexpr uintptr_t RakPeerVirtualTable = 0x6ec0cd8;
         inline constexpr uintptr_t RaknetReportNetworkError = 0x47b8110;
         inline constexpr uintptr_t SendPacketsToSelf = 0x2852f50;
         inline constexpr uintptr_t UpdateNetworkLoop = 0x495fae0;
         inline constexpr uintptr_t convertItemEnumToString = 0x4819f10;
    }

    namespace RbxTransport {
         inline constexpr uintptr_t AppDestructor = 0x2155f90;
         inline constexpr uintptr_t AppRTTI = 0x82cfb90;
         inline constexpr uintptr_t AppReceive = 0x2150b30;
         inline constexpr uintptr_t AppReceiveMaxBytes = 0x2150c30;
         inline constexpr uintptr_t AppSend = 0x214fe00;
         inline constexpr uintptr_t AppVTable = 0x6eb3930;
         inline constexpr uintptr_t ClientChannelConfig = 0x3a87510;
         inline constexpr uintptr_t ClientDestructor = 0x3a86c50;
         inline constexpr uintptr_t ClientRTTI = 0x833b3b8;
         inline constexpr uintptr_t ClientReceive = 0x3a87330;
         inline constexpr uintptr_t ClientSend = 0x3a86cc0;
         inline constexpr uintptr_t ClientVTable = 0x6f2cc08;
         inline constexpr uintptr_t FailureFallbackToRbxTransport = 0x47b75b5;
         inline constexpr uintptr_t StreamClose = 0x214fe80;
         inline constexpr uintptr_t UseRbxTransportClient = 0x3a6cc65;
    }

    namespace RemoteEvent {
         inline constexpr uintptr_t BaseVTableRva = 0x6f1bfb0;
         inline constexpr uintptr_t DescBaseVTableRva = 0x6f1bd48;
         inline constexpr uintptr_t FireClient = 0x3449d10;
         inline constexpr uintptr_t FireServer = 0x3449b70;
         inline constexpr uintptr_t FireServerRva = 0x71e7c0;
         inline constexpr uintptr_t FireServerVtableSlot = 0x4b;
         inline constexpr uintptr_t HookSlot7 = 0x7;
         inline constexpr uintptr_t HookSlot7RemoteEventFn = 0x3523e80;
         inline constexpr uintptr_t InstanceParentOffset = 0x68;
         inline constexpr uintptr_t InstanceVTableRva = 0x6ea8708;
         inline constexpr uintptr_t RemoteFuncVTableRva = 0x6f216c0;
         inline constexpr uintptr_t VTableRva = 0x6f21928;
         inline constexpr uintptr_t VtableSlotSignalFire = 0x2;
    }

    namespace RenderJob {
         inline constexpr uintptr_t FakeDataModel = 0x38;
         inline constexpr uintptr_t RealDataModel = 0x1f0;
         inline constexpr uintptr_t RenderView = 0x1e0;
    }

    namespace RenderQueue {
         inline constexpr std::uint32_t AlwaysOnTop = 13u;
         inline constexpr std::uint32_t AlwaysOnTopAdorns = 14u;
         inline constexpr std::uint32_t Decals = 2u;
         inline constexpr std::uint32_t Glass = 8u;
         inline constexpr std::uint32_t GlassTint = 7u;
         inline constexpr std::uint32_t OnTopReadOnlyDepth = 12u;
         inline constexpr std::uint32_t OnTopWithDepth = 11u;
         inline constexpr std::uint32_t Opaque = 0u;
         inline constexpr std::uint32_t OpaqueAdorns = 4u;
         inline constexpr std::uint32_t OpaqueCasters = 3u;
         inline constexpr std::uint32_t OpaqueWithAlpha = 5u;
         inline constexpr std::uint32_t Screen = 15u;
         inline constexpr std::uint32_t ScreenOnTopOfBlur = 16u;
         inline constexpr std::uint32_t Terrain = 1u;
         inline constexpr std::uint32_t Transparent = 9u;
         inline constexpr std::uint32_t TransparentCasters = 10u;
         inline constexpr std::uint32_t Water = 6u;
    }

    namespace RenderView {
         inline constexpr uintptr_t DeviceD3D11 = 0x8;
         inline constexpr uintptr_t LightingValid = 0x278;
         inline constexpr uintptr_t SkyValid = 0x2dc;
         inline constexpr uintptr_t VisualEngine = 0x18;
    }

    namespace RunService {
         inline constexpr uintptr_t HeartbeatFPS = 0xc8;
         inline constexpr uintptr_t HeartbeatTask = 0xe0;
    }

    namespace Script {
         inline constexpr uintptr_t ByteCode = 0x180;
         inline constexpr uintptr_t GUID = 0xc0;
         inline constexpr uintptr_t Hash = 0x190;
    }

    namespace ScriptContext {
         inline constexpr uintptr_t Resume = 0x4258330;
    }

    namespace Seat {
         inline constexpr uintptr_t Occupant = 0x208;
    }

    namespace ShaderManager {
         inline constexpr uintptr_t VTableRva = 0x6f2a8a8;
    }

    namespace Sky {
         inline constexpr uintptr_t CubeTextures = 0x2ea7f60;
         inline constexpr uintptr_t DrawSkyEnv = 0x377be00;
         inline constexpr uintptr_t MoonAngularSize = 0x234;
         inline constexpr uintptr_t MoonTextureId = 0xb8;
         inline constexpr uintptr_t SkyGroup = 0x8004a08;
         inline constexpr uintptr_t SkyboxBk = 0xe8;
         inline constexpr uintptr_t SkyboxDn = 0x118;
         inline constexpr uintptr_t SkyboxFt = 0x148;
         inline constexpr uintptr_t SkyboxLf = 0x178;
         inline constexpr uintptr_t SkyboxOrientation = 0x228;
         inline constexpr uintptr_t SkyboxRt = 0x1a8;
         inline constexpr uintptr_t SkyboxUp = 0x1d8;
         inline constexpr uintptr_t StarCount = 0x238;
         inline constexpr uintptr_t SunAngularSize = 0x22c;
         inline constexpr uintptr_t SunTextureId = 0x208;
    }

    namespace Sound {
         inline constexpr uintptr_t IsPlaying = 0x130;
         inline constexpr uintptr_t Looped = 0x12d;
         inline constexpr uintptr_t PlaybackSpeed = 0x10c;
         inline constexpr uintptr_t RollOffMaxDistance = 0x110;
         inline constexpr uintptr_t RollOffMinDistance = 0x114;
         inline constexpr uintptr_t SoundGroup = 0xd8;
         inline constexpr uintptr_t SoundId = 0xb8;
         inline constexpr uintptr_t Volume = 0x120;
    }

    namespace SpawnLocation {
         inline constexpr uintptr_t AllowTeamChangeOnTouch = 0x1e2;
         inline constexpr uintptr_t Enabled = 0x1e1;
         inline constexpr uintptr_t ForcefieldDuration = 0x34;
         inline constexpr uintptr_t Neutral = 0x3d;
         inline constexpr uintptr_t TeamColor = 0x3c;
    }

    namespace SpecialMesh {
         inline constexpr uintptr_t MeshId = 0xe8;
         inline constexpr uintptr_t Scale = 0xb4;
    }

    namespace StatsItem {
         inline constexpr uintptr_t Value = 0x180;
    }

    namespace SunRaysEffect {
         inline constexpr uintptr_t Enabled = 0xa0;
         inline constexpr uintptr_t Intensity = 0xa8;
         inline constexpr uintptr_t Spread = 0xac;
    }

    namespace SurfaceAppearance {
         inline constexpr uintptr_t AlphaMode = 0x1e0;
         inline constexpr uintptr_t Color = 0x1c8;
         inline constexpr uintptr_t ColorMap = 0xb8;
         inline constexpr uintptr_t EmissiveMaskContent = 0xe8;
         inline constexpr uintptr_t EmissiveStrength = 0x1e4;
         inline constexpr uintptr_t EmissiveTint = 0x1d4;
         inline constexpr uintptr_t MetalnessMap = 0x118;
         inline constexpr uintptr_t NormalMap = 0x148;
         inline constexpr uintptr_t RoughnessMap = 0x178;
    }

    namespace Task {
         inline constexpr uintptr_t TaskDelay = 0x43246d0;
         inline constexpr uintptr_t TaskDesynchronize = 0x4323210;
         inline constexpr uintptr_t TaskSynchronize = 0x4322da0;
         inline constexpr uintptr_t TaskWait = 0x43249d0;
    }

    namespace TaskScheduler {
         inline constexpr uintptr_t JobEnd = 0xd0;
         inline constexpr uintptr_t JobName = 0x18;
         inline constexpr uintptr_t JobStart = 0xc8;
         inline constexpr uintptr_t MaxFPS = 0xb0;
         inline constexpr uintptr_t Pointer = 0x8d71348;
         inline constexpr uintptr_t StepFunction = 0x2a22220;
    }

    namespace Team {
         inline constexpr uintptr_t BrickColor = 0xa8;
    }

    namespace TechniqueArray {
         inline constexpr uintptr_t BeginOffset = 0x0;
         inline constexpr uintptr_t EndOffset = 0x8;
         inline constexpr uintptr_t EntryStride = 0x88;
    }

    namespace Terrain {
         inline constexpr uintptr_t GrassLength = 0x1e0;
         inline constexpr uintptr_t MaterialColors = 0x4a8;
         inline constexpr uintptr_t WaterColor = 0x1d0;
         inline constexpr uintptr_t WaterReflectance = 0x1e8;
         inline constexpr uintptr_t WaterTransparency = 0x1ec;
         inline constexpr uintptr_t WaterWaveSize = 0x1f0;
         inline constexpr uintptr_t WaterWaveSpeed = 0x1f4;
    }

    namespace TextureManager2 {
         inline constexpr uintptr_t VTableRva = 0x6f28da0;
    }

    namespace Textures {
         inline constexpr uintptr_t Decal_Texture = 0x1d0;
         inline constexpr uintptr_t Texture_Texture = 0x1d0;
    }

    namespace Tool {
         inline constexpr uintptr_t CanBeDropped = 0x4a8;
         inline constexpr uintptr_t Enabled = 0x4a9;
         inline constexpr uintptr_t Grip = 0x49c;
         inline constexpr uintptr_t ManualActivationOnly = 0x4aa;
         inline constexpr uintptr_t RequiresHandle = 0x9d;
         inline constexpr uintptr_t TextureId = 0x350;
         inline constexpr uintptr_t Tooltip = 0x458;
    }

    namespace Types {
         inline constexpr uintptr_t AllTypes = 0x8d5c788;
    }

    namespace UnionOperation {
         inline constexpr uintptr_t AssetId = 0x300;
    }

    namespace UserInputService {
         inline constexpr uintptr_t WindowInputState = 0x2b0;
    }

    namespace Value {
         inline constexpr uintptr_t Value = 0xa8;
    }

    namespace VehicleSeat {
         inline constexpr uintptr_t MaxSpeed = 0x218;
         inline constexpr uintptr_t SteerFloat = 0x21c;
         inline constexpr uintptr_t ThrottleFloat = 0x220;
         inline constexpr uintptr_t Torque = 0x224;
         inline constexpr uintptr_t TurnSpeed = 0x228;
    }

    namespace ViewBase {
         inline constexpr uintptr_t VTableRva = 0x6f28260;
    }

    namespace VisualEngine {
         inline constexpr uintptr_t Dimensions = 0xb10;
         inline constexpr uintptr_t FakeDataModel = 0xaf0;
         inline constexpr uintptr_t Pointer = 0x884c2e0;
         inline constexpr uintptr_t RenderView = 0xc38;
         inline constexpr uintptr_t ViewMatrix = 0x1b0;
    }

    namespace Weld {
         inline constexpr uintptr_t Part0 = 0x108;
         inline constexpr uintptr_t Part1 = 0x118;
    }

    namespace WeldConstraint {
         inline constexpr uintptr_t Part0 = 0xa8;
         inline constexpr uintptr_t Part1 = 0xb8;
    }

    namespace WindowInputState {
         inline constexpr uintptr_t CapsLock = 0x40;
         inline constexpr uintptr_t CurrentTextBox = 0x48;
    }

    namespace Workspace {
         inline constexpr uintptr_t CurrentCamera = 0x4a8;
         inline constexpr uintptr_t DistributedGameTime = 0x4c8;
         inline constexpr uintptr_t ReadOnlyGravity = 0x9c8;
         inline constexpr uintptr_t World = 0x400;
    }

    namespace World {
         inline constexpr uintptr_t AirProperties = 0x238;
         inline constexpr uintptr_t FallenPartsDestroyHeight = 0x214;
         inline constexpr uintptr_t Gravity = 0x220;
         inline constexpr uintptr_t Primitives = 0x2c8;
         inline constexpr uintptr_t worldStepsPerSec = 0x880;
    }

    namespace WorldRoot {
         inline constexpr uintptr_t FindPartOnRayBoundFnRva = 0xd65530;
         inline constexpr uintptr_t FindPartOnRayDescriptorRva = 0x8558060;
         inline constexpr uintptr_t FindPartOnRayWithIgnoreListBoundFnRva = 0xd655b0;
         inline constexpr uintptr_t FindPartOnRayWithIgnoreListDescriptorRva = 0x8558120;
         inline constexpr uintptr_t FindPartOnRayWithWhitelistBoundFnRva = 0xd65640;
         inline constexpr uintptr_t FindPartOnRayWithWhitelistDescriptorRva = 0x85581e0;
         inline constexpr uintptr_t RaycastBoundFnRva = 0xd5c500;
         inline constexpr uintptr_t RaycastDescriptorRva = 0x8557620;
         inline constexpr uintptr_t RaycastDescriptorVtableRva = 0x6e0ad60;
    }

    namespace Camera {
        inline constexpr uintptr_t ViewportInt16 = Viewport;
    }
    namespace Instance {
        inline constexpr uintptr_t ClassName = 0x8;
        inline constexpr uintptr_t ChildrenStride = 0x10;
    }
    namespace Humanoid {
        inline constexpr uintptr_t WalkSpeed = Walkspeed;
        inline constexpr uintptr_t WalkSpeedCheck = WalkspeedCheck;
    }
    namespace Players {
        inline constexpr uintptr_t LocalPlayer = Player::LocalPlayer;
    }
    namespace Primitive {
        inline constexpr uintptr_t PrimitiveFlags = Flags;
    }
    namespace Lighting {
        inline constexpr uintptr_t ShadowSoftness = 0xe8;
    }
    namespace WorldRoot {
        inline constexpr uintptr_t RaycastBoundDesc = RaycastDescriptorRva;
        inline constexpr uintptr_t RaycastBoundFn = 0x90;
    }

}
