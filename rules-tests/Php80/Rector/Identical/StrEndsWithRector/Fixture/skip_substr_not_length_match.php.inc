<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SkipSubstrNotLengthMatch
{
    const BUNDLE = 'value';

    public function run()
    {
        // incorrect length
        $isMatch = substr($haystack, -10) === self::BUNDLE;
        $isMatch = self::BUNDLE === substr($haystack, -10);
        $isMatch = substr($haystack, -10) === 'value';
        $isMatch = 'value' === substr($haystack, -10);

        // correct length, missing unary negation
        $isMatch = substr($haystack, 5) === self::BUNDLE;
        $isMatch = self::BUNDLE === substr($haystack, 5);
        $isMatch = substr($haystack, 5) === 'value';
        $isMatch = 'value' === substr($haystack, 5);

        // incorrect length
        $isNotMatch = substr($haystack, -10) !== self::BUNDLE;
        $isNotMatch = self::BUNDLE !== substr($haystack, -10);
        $isNotMatch = substr($haystack, -10) !== 'value';
        $isNotMatch = 'value' !== substr($haystack, -10);

        // correct length, missing unary negation
        $isNotMatch = substr($haystack, 5) !== self::BUNDLE;
        $isNotMatch = self::BUNDLE !== substr($haystack, 5);
        $isNotMatch = substr($haystack, 5) !== 'value';
        $isNotMatch = 'value' !== substr($haystack, 5);
    }
}
