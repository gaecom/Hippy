/*
 *
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include <jni.h>

#include "core/napi/js_native_api_types.h"
#include "hippy.h"

#ifndef ANDROID_DEMO_CONVERT_UTILS_H
#define ANDROID_DEMO_CONVERT_UTILS_H

struct JNIArgs {
  JNIArgs(size_t count) : args_(count) {}

  std::vector<jvalue> args_;
  std::vector<jobject> global_refs_;
};

template <typename T>
std::string ToString(T v) {
  std::ostringstream stream;
  stream << v;
  return stream.str();
}

struct MethodInfo {
  std::string signature_;
  jmethodID method_id_ = nullptr;
};

class ConvertUtils {
 public:
  static bool Init();

  static bool Destory();

  static std::vector<std::string> GetMethodArgTypesFromSignature(
      const std::string &method_signature);

  static std::shared_ptr<JNIArgs> ConvertJSIArgsToJNIArgs(
      hippy::napi::TurboEnv &turbo_env,
      const std::string &module_name,
      const std::string &method_name,
      const std::vector<std::string> &method_arg_types,
      const std::vector<std::shared_ptr<hippy::napi::CtxValue>> &arg_values);

  static std::shared_ptr<hippy::napi::CtxValue> ConvertMethodResultToJSValue(
      hippy::napi::TurboEnv &turbo_env,
      const jobject &obj,
      const MethodInfo &method_info,
      const jvalue *args);

  static jobject ToJObject(hippy::napi::TurboEnv &turbo_env,
                           const std::shared_ptr<hippy::napi::CtxValue> &value);

  static jobject ToHippyMap(
      hippy::napi::TurboEnv &turbo_env,
      const std::shared_ptr<hippy::napi::CtxValue> &value);

  static jobject ToHippyArray(
      hippy::napi::TurboEnv &turbo_env,
      const std::shared_ptr<hippy::napi::CtxValue> &value);

  static std::shared_ptr<hippy::napi::CtxValue> ToJsValueInArray(
      hippy::napi::TurboEnv &turbo_env,
      const jobject &array,
      int index);

  static std::shared_ptr<hippy::napi::CtxValue> ToJsArray(
      hippy::napi::TurboEnv &turbo_env,
      const jobject &array);

  static std::shared_ptr<hippy::napi::CtxValue> ToJsMap(
      hippy::napi::TurboEnv &turbo_env,
      const jobject &map);

  static bool HandleBasicType(
      hippy::napi::TurboEnv &turbo_env,
      const std::string &type,
      jvalue &j_args,
      const std::shared_ptr<hippy::napi::CtxValue> &value);

  static bool HandleObjectType(
      hippy::napi::TurboEnv &turbo_env,
      const std::string &module_name,
      const std::string &method_name,
      const std::string &type,
      jvalue &j_args,
      const std::shared_ptr<hippy::napi::CtxValue> &value,
      std::vector<jobject> &global_refs);

  static void ThrowException(const std::shared_ptr<hippy::napi::Ctx> &ctx,
                             const std::string &info);

  static std::unordered_map<std::string, MethodInfo> GetMethodMap(
      const std::string &method_map_str);

  static std::shared_ptr<hippy::napi::CtxValue> ToHostObject(
      hippy::napi::TurboEnv &turbo_env,
      jobject &j_obj,
      std::string name);
};

static jclass hippy_array_clazz;
static jmethodID hippy_array_constructor;
static jmethodID hippy_array_push_object;
// get
static jmethodID hippy_array_size;
static jmethodID hippy_array_get_sig;
static jmethodID hippy_array_get;

static jclass hippy_map_clazz;
static jmethodID hippy_map_constructor;
static jmethodID hippy_map_push_object;
static jmethodID to_hippy_array;

static jclass integer_clazz;
static jclass double_clazz;
static jclass float_clazz;
static jclass long_clazz;
static jclass boolean_clazz;
static jmethodID integer_constructor;
static jmethodID double_constructor;
static jmethodID double_value;
static jmethodID float_constructor;
static jmethodID long_constructor;
static jmethodID boolean_constructor;
static jmethodID boolean_value;

static jclass promise_clazz;
static jmethodID promise_constructor;

const std::string kint = "I";
const std::string kdouble = "D";
const std::string kfloat = "F";
const std::string klong = "J";
const std::string kboolean = "Z";
const std::string kInteger = "Ljava/lang/Integer;";
const std::string kDouble = "Ljava/lang/Double;";
const std::string kFloat = "Ljava/lang/Float;";
const std::string kLong = "Ljava/lang/Long;";
const std::string kString = "Ljava/lang/String;";
const std::string kBoolean = "Ljava/lang/Boolean;";
const std::string kHippyArray = "Lcom/tencent/mtt/hippy/common/HippyArray;";
const std::string kHippyMap = "Lcom/tencent/mtt/hippy/common/HippyMap;";
const std::string kPromise = "Lcom/tencent/mtt/hippy/modules/Promise;";
const std::string kvoid = "V";
const std::string kUnSupportedType = "Lcom/invalid;";

#endif  // ANDROID_DEMO_CONVERT_UTILS_H
