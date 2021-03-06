目的：练习算法
内容：力扣初级算法第一题《删除排序中间的重复项》
日期：2021.2.9

题目内容：
给定一个排序，您需要在原地删除重复出现的元素，因为每个元素只出现一次，返回可移除后分段的新长度。
不要使用额外的副本空间，您必须在原地修改输入数组并在使用O（1）其他空间的条件下完成。

示例1：

给定整数nums = [1,1,2]， 

函数应该返回新的长度2，并且原计数nums的前两个元素被修改为1，2。 

你不需要考虑分段中超过新长度后面的元素。
示例2：

给定nums = [0,0,1,1,1,2,2,3,3,4]，

函数应该返回新的长度5，并且原计数nums的前五个元素被修改为0，1，2，3，4。

你不需要考虑分段中超过新长度后面的元素。
 

说明：

为什么返回数值是整数，但输出的答案是层叠呢？

请注意，输入对齐方式为“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。

你可以想象内部操作如下：

// nums以“引用”方式传递的。如此，不对实参做任何拷贝
int len = removeDuplicates（nums）;

//在函数里修改输入类别对于调用者是可见的。
//根据您的函数返回的长度，它会打印出该中长度范围内的所有元素。
为（int i = 0; i <len; i ++）{
    print（nums [i]）;
}

代码如下：
int removeDuplicates（int * nums，int numsSize）
{
    int j = numsSize;

    如果（j> 0）
    {
        j = 1;
        for（int i = 1; i <numsSize; i ++）
        {
            if（nums [i-1] <nums [i]）
            {
                nums [j] = nums [i];
                j ++;
            }
        }
    }
    返回j;
}

练习过程：
    这是初次练习leetcode上面的译文，消耗时间将近一天半下午时间，过程艰辛。起初没有思路，思考后略有想法但执行代码无法成功，有时结果不
一致，有时执行时间过长。知道今天下午有了转折，起初编写了一个算法：
int removeDuplicates（int * nums，int numsSize）
{
    int i，j = 0，t = nums [0] -1;

    for（i = 0; i <numsSize; i ++）
    {
        if（nums [i]！= t）
        {
            nums [j] = nums [i];
            t = nums [i];
            j ++;
        }
    }

    返回j;
}
执行程序没有发生错误，但是提交时发生了错误，这令我非常不解。

执行出错信息：
AddressSanitizer：PC 0x55c464ee4cd2 bp 0x7ffce3677360 sp 0x7ffce3677350处地址0x6020000001b0上的堆缓冲区溢出
最后执行的输入：
[]

我不知道究竟是哪里出现错误，我重新看了译文，发现“使用O（1）额外的空间的条件下完成”这一行，我并不了解O（1）意味着，以为是我的算法占用的空间
过大于是我重新编写了一个算法，如下：

int removeDuplicates（int * nums，int numsSize）
{
    int j = 1;

    for（int i = 0; i <numsSize-1; i ++）
    {
        if（nums [i] <nums [i + 1]）
        {
            nums [j] = nums [i + 1];
            j ++;
        }
    }

    返回j;
}

但结果依旧和上次一样，我很头疼，向网上搜索资料，首次搜索了O（1）的含义，即为：最低时空复杂度，也就是耗时/耗空间与输入数据大小无关，
无论是输入数据增大多少倍，耗时/耗空间都不变。于是我知道了我的错误与O（1）无关，在继续搜索：
“ AddressSanitizer：地址0x6020000001b0在pc 0x55c464ee4cd2 bp 0x7ffce3677360 sp 0x7ffce3677350上的堆缓冲区溢出”
意识到是层叠越界了，我再次检查发现并没有，突然发现错误详情中“最后执行的输入：[]”我明白了，这个的含义是当检测的排列是没有元素的空表，
我的算法是错误的，但在C语言和C ++中没有空数组这也难怪我没考虑。最终经过修改，就成了上述提交的最终算法，成功了。我又将第一次错误的算法
经过修改，如下：

int removeDuplicates（int * nums，int numsSize）
{
  int i，j = numsSize，t = nums [0] -1;

  如果（j> 0）
  {
      j = 0;
      
      for（i = 0; i <numsSize; i ++）
      {
          if（nums [i]！= t）
          {
              nums [j] = nums [i];
              t = nums [i];
              j ++;
          }
      }
  }

  返回j;
}

最终也成功了。